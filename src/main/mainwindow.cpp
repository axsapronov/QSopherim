#include "mainwindow.h"

#include <QDesktopWidget> /// moved to center


#include "abstractcontroller.h"
#include "abstractmodel.h"
#include "abstractview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Включаем наш QML
    ui = new QDeclarativeView;
    ui->setSource(QUrl("qrc:/view/view/mainwindow.qml"));
    setCentralWidget(ui);
    ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    //Находим корневой элемент
    Root = ui->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент window
    ui->rootContext()->setContextProperty("window", this);

    /// moved to center desktop
    QRect rect = QApplication::desktop()->availableGeometry(this);
    this->move(rect.width() / 2 - this->width() / 2,
               rect.height() / 2 - this->height() / 2);


    AbstractModel model;
    AbstractView view(&model);
    AbstractController controller(&model);
    controller.start();


    /// maximized
    //    this->showMaximized();
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    //Удаляем QML
    delete ui;
}
//------------------------------------------------------------------------------
void MainWindow::FunctionC()
{
    //Найдем строку ввода
    QObject* textinput = Root->findChild<QObject*>("textinput");

    //Найдем поле вывода
    QObject* memo = Root->findChild<QObject*>("memo");

    QString str;//Создадим новую строковую переменную

    //Считаем информацию со строки ввода через свойство text
    str=(textinput->property("text")).toString();

    int a;
    a=str.toInt();//Переведем строку в число
    a++;//Добавим к числу 1

    QString str2;//Создадим еще одну строковую переменную
    str2=QString::number(a);//Переведем число в строку

    //Ну и наконец выведем в поле вывода нашу информацию
    memo->setProperty("text", str+"+1="+str2);
}
//------------------------------------------------------------------------------
