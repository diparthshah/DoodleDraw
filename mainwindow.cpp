#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPaintEvent>
#include<QPainter>
#include<QImage>
#include<QMouseEvent>
#include<QDesktopWidget>
#include<QInputDialog>
#include<QColorDialog>
#include<QFileDialog>
#include<QDebug>
#include<iostream>
#include<QMessageBox>
#define DEFAULT_SIZE 5;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mImage = new QImage(QApplication::desktop()->size(),QImage::Format_ARGB32_Premultiplied);
    mPainter = new QPainter(mImage);
    mEnabled = false;
    mColor=QColor(Qt::black);
    mSize=DEFAULT_SIZE;
    mCapStyle=brushDialog->bCapStyle;
    mPenLineStyle=brushDialog->bPenLineStyle;
    mPenJoinStyle=brushDialog->bPenJoinStyle;
    mShape=0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mImage;
    delete mPainter;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(mImage->rect(),Qt::white);
    painter.drawImage(0,0,*mImage);
    e->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    mEnabled=true;
    mBegin=e->pos();
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(!mEnabled){
        e->accept();
        return;
    }

    switch(mShape){
        case 0:
            mEnd=e->pos();
            BrushTool();
            break;
        default:
            /* do nothing */
            break;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    mEnabled=false;
    e->accept();
    update();
}

void MainWindow::BrushTool()
{
    mShape=0;
    mCapStyle = brushDialog->bCapStyle;
    mPenJoinStyle = brushDialog->bPenJoinStyle;
    mPenLineStyle = brushDialog->bPenLineStyle;
    QPen pen(mColor);
    pen.setCapStyle(mCapStyle);
    pen.setStyle(mPenLineStyle);
    pen.setWidth(mSize);
    pen.setJoinStyle(mPenJoinStyle);
    mPainter->setPen(pen);
    mPainter->drawLine(mBegin,mEnd);
    mBegin=mEnd;
    update();
}

void MainWindow::on_actionColors_triggered()
{
    mColor=QColorDialog::getColor(Qt::black,this,"Color");
    update();
}

void MainWindow::on_actionBrush_Size_triggered()
{
    mSize=QInputDialog::getInt(this,"Brush Size","Size",5,1);
    update();
}

void MainWindow::on_actionShapes_triggered()
{
    QStringList ShapesList;
    ShapesList<<"Line";
    ShapesList<<"Rectangle";

    QString shapesData = QInputDialog::getItem(this,"Choose Shape","Options",ShapesList);

    if(shapesData=="Line"){
        mShape=1;
    }

    if(shapesData=="Rectangle"){
        mShape=2;
    }

    update();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"File Name","/home/diparth/untitled.png","*.png");
    bool save = mImage->save(fileName,nullptr,100);

    if(save){
        QMessageBox::information(this,"Doodle Draw","File Saved");
    }
    else{
        QMessageBox::warning(this,"Doodle Draw","Cant Save File");
    }

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open File","/home/",tr("Image Files (*.png *.jpg *.bmp)"));
    bool save = mImage->load(fileName,nullptr);

    if(save){
        QMessageBox::information(this,"Doodle Draw","Your file is now open");
    }
    else{
        QMessageBox::warning(this,"Doodle Draw","Cannot open file");
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionBrushOptions_triggered()
{
    brushDialog = new BrushDialog(this);
    brushDialog->setWindowTitle("Doodle Brush Options");
    brushDialog->show();
}
