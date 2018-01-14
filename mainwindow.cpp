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
    mCapStyle=Qt::SquareCap;
    mPenLineStyle=Qt::SolidLine;
    mPenJoinStyle=Qt::BevelJoin;
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
    painter.end();
    update();
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

  QPen pen(mColor);
  pen.setCapStyle(mCapStyle);
  pen.setStyle(mPenLineStyle);
  pen.setWidth(mSize);
  pen.setJoinStyle(mPenJoinStyle);
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
    update();
}

void MainWindow::on_actionColors_triggered()
{
    mColor=QColorDialog::getColor(Qt::black,this,"Color");
}

void MainWindow::on_actionBrush_Size_triggered()
{
    mSize=QInputDialog::getInt(this,"Brush Size","Size",5,1);
}

void MainWindow::on_actionCapStyle_triggered()
{
    QStringList CapStyleList;
    CapStyleList<<"SquareCap";
    CapStyleList<<"FlatCap";
    CapStyleList<<"RoundCap";

    QString capStyleData = QInputDialog::getItem(this,"Choose CapStyle","Options",CapStyleList);

    if(capStyleData=="FlatCap"){
        mCapStyle=Qt::FlatCap;
    }

    if(capStyleData=="RoundCap"){
        mCapStyle=Qt::RoundCap;
    }

    if(capStyleData=="SquareCap"){
        mCapStyle=Qt::SquareCap;
    }

    update();
}

void MainWindow::on_actionLine_Style_triggered()
{
    QStringList LineStyleList;
    LineStyleList<<"SolidLine";
    LineStyleList<<"DashLine";
    LineStyleList<<"DotLine";
    LineStyleList<<"DashDotLine";
    LineStyleList<<"DashDotDotLine";

    QString lineStyleData = QInputDialog::getItem(this,"Choose LineStyle","Options",LineStyleList);

    if(lineStyleData=="SolidLine"){
        mPenLineStyle=Qt::SolidLine;
    }

    if(lineStyleData=="DashLine"){
        mPenLineStyle=Qt::DashLine;
    }

    if(lineStyleData=="DotLine"){
        mPenLineStyle=Qt::DotLine;
    }

    if(lineStyleData=="DashDotLine"){
        mPenLineStyle=Qt::DashDotLine;
    }

    if(lineStyleData=="DashDotDotLine"){
        mPenLineStyle=Qt::DashDotDotLine;
    }

    update();
}

void MainWindow::on_actionJoinStyle_triggered()
{
    QStringList JoinStyleList;
    JoinStyleList<<"BevelJoin";
    JoinStyleList<<"MiterJoin";
    JoinStyleList<<"RoundJoin";

    QString joinStyleData = QInputDialog::getItem(this,"Choose JoinStyle","Options",JoinStyleList);

    if(joinStyleData=="BevelJoin"){
        mPenJoinStyle=Qt::BevelJoin;
    }

    if(joinStyleData=="MiterJoin"){
        mPenJoinStyle=Qt::MiterJoin;
    }
    if(joinStyleData=="RoundJoin"){
        mPenJoinStyle=Qt::RoundJoin;
    }
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
