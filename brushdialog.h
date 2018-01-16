#ifndef BRUSHDIALOG_H
#define BRUSHDIALOG_H

#include <QDialog>

namespace Ui {
class BrushDialog;
}

class BrushDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrushDialog(QWidget *parent = 0);
    ~BrushDialog();
    QColor bColor;
    Qt::PenCapStyle bCapStyle;
    Qt::PenStyle bPenLineStyle;
    Qt::PenJoinStyle bPenJoinStyle;
    int bSize;

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::BrushDialog *ui;
};

#endif // BRUSHDIALOG_H
