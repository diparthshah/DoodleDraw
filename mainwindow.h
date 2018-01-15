#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QPainter;
class QImage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
private slots:
    void on_actionColors_triggered();
    void on_actionBrush_Size_triggered();
    void on_actionCapStyle_triggered();
    void on_actionLine_Style_triggered();
    void on_actionJoinStyle_triggered();
    void on_actionShapes_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QPainter *mPainter;
    QImage *mImage;
    QPoint mBegin;
    QPoint mEnd;
    bool mEnabled;
    bool drawStarted;
    int mSize;
    QColor mColor;
    Qt::PenCapStyle mCapStyle;
    Qt::PenStyle mPenLineStyle;
    Qt::PenJoinStyle mPenJoinStyle;
    int mShape;
    QLine mLine;
    //QRect mRect;
};
#endif // MAINWINDOW_H
