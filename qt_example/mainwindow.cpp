#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src_dll\core.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _obj_signal(48000, 720)
{
    ui->setupUi(this);
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::on_Timeout);
    _timer->start(500);

    _obj_signal.AddHarmonic(1,100);
    _obj_signal.AddNoiseNormalDist(0.075,0,1);
    _flag_render = false;
}

MainWindow::~MainWindow()
{
    delete _timer;
    delete ui;
}

void MainWindow::RenderSignal(){
    // Очищаем все графики
    ui->widget->clearGraphs();
    // Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(_obj_signal.GetSignal()[0],
                                  _obj_signal.GetSignal()[1]);
    // Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("Time");
    ui->widget->yAxis->setLabel("Value Signal");

    // Установим область, которая будет показываться на графике
    double min_x = _obj_signal.GetMinValueTime();
    double max_x = _obj_signal.GetMaxValueTime();
    double min_y = _obj_signal.GetMinValueSignal();
    double max_y = _obj_signal.GetMaxValueSignal();
    ui->widget->xAxis->setRange(min_x,max_x); // Для оси Ox
    ui->widget->yAxis->setRange(min_y,max_y); // Для оси Oy
    ui->widget->replot(); // Отрисовка
}
void MainWindow::on_Timeout(){
    if( !_flag_render ){
        RenderSignal();
        _flag_render = true;
    }
}


void MainWindow::on_comboBox_1_currentIndexChanged(int index){ // Enter distrebution
    switch(index)  {
        case 0: {
            ui->lineEdit_4->setText("Param. -  0");
            ui->lineEdit_5->setText("Param. -  1");
            _type_distibution = 0;
            break;
         }
        case 1: { // Uniform distribution;
            ui->lineEdit_4->setText("min");
            ui->lineEdit_5->setText("max");
            _type_distibution = 1;
            break;
        }
        case 2:{ // normal distribution;
            ui->lineEdit_4->setText("mean");
            ui->lineEdit_5->setText("sigma");
            _type_distibution = 2;
            break;
        }
    }

}

void MainWindow::on_pushButton_0_clicked() { // button Enter parameters for generator
    std::int32_t fs;
    std::int32_t sample;
    QString read_text;
    read_text = ui->lineEdit_0->text();
    fs = read_text.toUInt();
    read_text = ui->lineEdit_1->text();
    sample = read_text.toUInt();

    _obj_signal.Clear();

    if( (fs && sample) > 0){
        _obj_signal.ResetParameters(fs,sample);
        _flag_render = false;
    }
}


void MainWindow::on_pushButton_2_clicked(){ // Add signal
    double ampl;
    std::int32_t f;
    QString read_text;
    read_text = ui->lineEdit_2->text();
    ampl = read_text.toDouble();
    read_text = ui->lineEdit_3->text();
    f = read_text.toUInt();

    if( (ampl != 0) && f > 0 ){
        switch(ui->comboBox_0->currentIndex()){
        case 0:
            _obj_signal.AddHarmonic(ampl,f);
            break;
        case 1:
            _obj_signal.AddMeander(ampl,f);
            break;
        case 2:
            _obj_signal.AddSaw(ampl,f);
            break;
        case 3:
            _obj_signal.AddTriangle(ampl,f);
            break;
        case 4:
             _obj_signal.AddSinglePeriod(ampl,f);
            break;
        case 5:
            _obj_signal.AddRectified(ampl,f);
            break;
        }
        _flag_render = false;
    }

}

void MainWindow::on_pushButton_3_clicked() { // Add noise
    double param_0;
    double param_1;
    double ampl;
    QString read_text;
    read_text = ui->lineEdit_4->text();
    param_0 = read_text.toDouble();
    read_text = ui->lineEdit_5->text();
    param_1 = read_text.toDouble();
    read_text = ui->lineEdit_6->text();
    ampl = read_text.toDouble();
    if (ampl > 0){
        switch (_type_distibution){
        case 1:
            _obj_signal.AddNoiseUniformDist(ampl, param_0, param_1);
            break;
        case 2:
            _obj_signal.AddNoiseNormalDist(ampl,param_0,param_1);
            break;
        }
    }
    _flag_render = false;
}

void MainWindow::on_pushButton_1_clicked(){ // button clear
    _obj_signal.Clear();
    _flag_render = false;
}
