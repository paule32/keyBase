#ifndef EDITORGUTTER_H
#define EDITORGUTTER_H

#include <QPainter>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QPlainTextEdit>
#include <QSyntaxHighlighter>

class Highlighter;
class EditorGutter;

class MyEditor: public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MyEditor  (class QWidget *parent = 0);
    void linePaintEvent(class QPaintEvent *event) ;
    int  gutterWidth();
    int  lines;
protected:
    void mousePressEvent(class QMouseEvent  *event) Q_DECL_OVERRIDE;
    void keyPressEvent  (class QKeyEvent    *event) Q_DECL_OVERRIDE;
    void resizeEvent    (class QResizeEvent *event) Q_DECL_OVERRIDE;
public slots:
    void on_cursorPositionChanged();
    void on_gutterUpdate(int);
    void on_linesUpdate(const QRect &rect, int dy);
private:
    class Highlighter  * highlighter;
    class EditorGutter * gutter;
public slots:
    void on_dockHelpOpen();
    void on_parseText();
    void ShowContextMenu(const QPoint& pos);
signals:
    void onHelpF1();
};

extern class MyEditor *global_textedit;

class EditorGutter: public QWidget
{
    Q_OBJECT
public:
    explicit EditorGutter(class MyEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }
protected:
    void paintEvent(class QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->linePaintEvent(event);
    }
private:
    class MyEditor *codeEditor;
};


class Highlighter: public QSyntaxHighlighter
{
    Q_OBJECT
public:
    Highlighter(MyEditor *parent = 0);
protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
private:
    struct HighlightRule      {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightRule> HighlightRules;

    QRegExp commentStart, cppComment;
    QRegExp commentEnd;

    QTextCharFormat cppCommentFormat;
    QTextCharFormat multiLineCommentFormat;
};

extern MyEditor *global_textedit;
#endif // EDITORGUTTER_H
