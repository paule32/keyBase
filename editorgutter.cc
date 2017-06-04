#include "editorgutter.h"
#include "mainwindow.h"

extern MainWindow *w;
extern bool parseText(QString s);

MyEditor *global_textedit = NULL;

MyEditor::MyEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    setObjectName("dBaseEditor");
    setWordWrapMode(QTextOption::NoWrap);
    setAcceptDrops(true);

	global_textedit = this;

    gutter = new EditorGutter(this);
    lines  = 1;

    //connect(this, SIGNAL(blockCountChanged(int)  ), this, SLOT(updateGutterWidth(int)));
    connect(this, SIGNAL(cursorPositionChanged() ), this, SLOT(on_cursorPositionChanged()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(on_linesUpdate(QRect,int)));

    highlighter = new Highlighter(this);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu(const QPoint&)));

    on_gutterUpdate(0);
    on_cursorPositionChanged();
}

void MyEditor::ShowContextMenu(const QPoint& pos) // this is a slot
{
    // for most widgets
    QPoint globalPos = mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myPopUp;

    myPopUp.addAction("Run ...");
    myPopUp.addSeparator();
    myPopUp.addAction("Insert template ...");
    myPopUp.addSeparator();
    myPopUp.addAction("Copy Text");
    myPopUp.addAction("Paste");

    QAction* selectedItem = myPopUp.exec(globalPos);

    if (selectedItem->text() == QString("Run ...")) {
        parseText(global_textedit
                   ->document()
                   ->toPlainText());
    }  else
    if (selectedItem->text() == QString("Insert template ..."))
    {
        std::string temp =
"** END HEADER -- Diese Zeile nicht löschen.\n"
"// Erstellt am 14.01.1997\n"
"//\n"
"parameter bModal\n"
"local f\n"
"f = new MainFormular()\n"
"if (bModal)\n"
"    f.mdi = .F.        && ensure mdi\n"
"    f.ReadModal()\n"
"else\n"
"    f.Open()\n"
"endif\n"
"\n"
"CLASS MainFormular OF FORM\n"
"\n"
"\n"
"ENDCLASS";
        this->document()->clear();
        this->document()->setPlainText(QString(temp.c_str()));
    }
    else
    {
        // nothing was chosen
    }
}

void MyEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    gutter->setGeometry(
    QRect(cr.left(),
          cr.top (), gutterWidth(),
          cr.height()));
}

void MyEditor::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        //w->close();
        break;

    case Qt::Key_F1:
        //on_dockHelpOpen();
        break;

    case Qt::Key_F2:
        on_parseText();
        break;

    case Qt::Key_Tab:
        insertPlainText("    ");
        break;

    default:
        QPlainTextEdit::keyPressEvent(event);
        break;
    }
}

void MyEditor::mousePressEvent(class QMouseEvent  *event)
{
    QPlainTextEdit::mousePressEvent(event);
    on_cursorPositionChanged();
}

void MyEditor::on_parseText()
{
    QString str;
    str = document()->toPlainText();
    parseText(str);
}

void MyEditor::on_dockHelpOpen() {
    //w->on_dockHelpOpen();
}

void MyEditor::on_cursorPositionChanged()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor =   textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void MyEditor::on_gutterUpdate(int) {
    setViewportMargins(gutterWidth(), 0,0,0);
}

void MyEditor::on_linesUpdate(const QRect &rect, int dy)
{
    if (dy)
    gutter->scroll(0,dy); else
    gutter->update(0,rect.y(),
    gutter->width() ,rect.height());

    if (rect.contains(viewport()->rect()))
       on_gutterUpdate(0);
}

void MyEditor::linePaintEvent(class QPaintEvent *event)
{
    QPainter painter(gutter);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).
                    translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    lines = 0;
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, gutter->width(),
                             fontMetrics().height(),
                             Qt::AlignRight, number);
            ++lines;
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

int MyEditor::gutterWidth()
{
    int digits = 2;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

Highlighter::Highlighter(MyEditor *parent)
    : QSyntaxHighlighter(parent->document())
{
    //HighlighterRule rule;

    cppCommentFormat.setForeground(Qt::red);
    cppCommentFormat.setFontWeight(QFont::Bold);
    cppCommentFormat.setFontItalic(true);

    commentStart = QRegExp("/\\*");
    commentEnd   = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    enum { NormalState = -1, InsideCStyleComment };

    int state = previousBlockState();
    int start = 0;

    for (int i = 0; i < text.length(); ++i) {
        if (state == InsideCStyleComment) {
            if (text.mid(i, 2) == "*/") {
                state = NormalState;
                setFormat(start, i - start + 2, cppCommentFormat);
            }   }   else {
            if (text.mid(i,2) == "**") {
                setFormat(i, text.length() - i, cppCommentFormat);
                break;
            }
            if (text.mid(i,2) == "&&") {
                setFormat(i, text.length() - i, cppCommentFormat);
                break;
            }
            // C++ comment
            if (text.mid(i,2) == "//") {
                setFormat(i, text.length() - i, cppCommentFormat);
                break;  }
                else if (text.mid(i, 2) == "/*") {
                start = i;
                state = InsideCStyleComment;
            }
        }
    }

    if (state == InsideCStyleComment)
    setFormat(start, text.length() - start, cppCommentFormat);

    setCurrentBlockState(state);
}
