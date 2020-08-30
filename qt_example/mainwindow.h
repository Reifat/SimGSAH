#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTimer>
#include "generator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Timeout();

    void on_comboBox_1_currentIndexChanged(int index);

    void on_pushButton_1_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void RenderSignal();
    Ui::MainWindow *ui;
    bool _flag_render;
    QTimer* _timer;
    Generator _obj_signal;
    std::uint16_t _type_distibution;
};
#endif // MAINWINDOW_H
