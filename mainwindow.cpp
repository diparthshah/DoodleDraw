#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPaintEvent>
#include<QPainter>
#include<QImage>
#include<QMouseEvent>
#include<QDesktopWidget>
#include<QInputDialog>
#include<QColorDialog>
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
    ui->toolBar->setIconSize(iconSize());
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
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(!mEnabled){
        e->accept();
        return;
    }
    QPen pen(mColor, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(mSize);
    mEnd=e->pos();
    mPainter->setPen(pen);
    mPainter->drawLine(mBegin,mEnd);
    mBegin=mEnd;
    update();
    e->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    mEnabled=false;
    e->accept();
}

void MainWindow::on_actionColors_triggered()
{
    mColor=QColorDialog::getColor(Qt::black,this,"Color");
}

void MainWindow::on_actionBrush_Size_triggered()
{
    mSize=QInputDialog::getInt(this,"Brush Size","Size",5,1);
}
