#include "brushdialog.h"
#include "ui_brushdialog.h"
#include<QColorDialog>

BrushDialog::BrushDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushDialog)
{
    ui->setupUi(this);
    bCapStyle=Qt::FlatCap;
    bPenJoinStyle=Qt::BevelJoin;
    bPenLineStyle=Qt::SolidLine;
}

BrushDialog::~BrushDialog()
{
    delete ui;
}

void BrushDialog::on_pushButton_ok_clicked()
{
    QString capstyle = ui->comboBox_capstyle->currentText();

    if(capstyle=="FlatCap"){
        bCapStyle=Qt::FlatCap;
    }

    if(capstyle=="RoundCap"){
        bCapStyle=Qt::RoundCap;
    }

    if(capstyle=="SquareCap"){
        bCapStyle=Qt::SquareCap;
    }

    QString joinstyle = ui->comboBox_joinstyle->currentText();

    if(joinstyle=="BevelJoin"){
        bPenJoinStyle=Qt::BevelJoin;
    }

    if(joinstyle=="MiterJoin"){
        bPenJoinStyle=Qt::MiterJoin;
    }
    if(joinstyle=="RoundJoin"){
        bPenJoinStyle=Qt::RoundJoin;
    }

    QString linestyle = ui->comboBox_linestyle->currentText();

    if(linestyle=="SolidLine"){
        bPenLineStyle=Qt::SolidLine;
    }

    if(linestyle=="DashLine"){
        bPenLineStyle=Qt::DashLine;
    }

    if(linestyle=="DotLine"){
        bPenLineStyle=Qt::DotLine;
    }

    if(linestyle=="DashDotLine"){
        bPenLineStyle=Qt::DashDotLine;
    }

    if(linestyle=="DashDotDotLine"){
        bPenLineStyle=Qt::DashDotDotLine;
    }

    close();
}
