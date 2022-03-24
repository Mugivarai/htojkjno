#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
, ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sockReady()
{
    if (socket->waitForConnected(500))
    {
        socket->waitForReadyRead(11500);
        Data = socket->readAll();

        doc = QJsonDocument::fromJson(Data, &docError);


        if (docError.errorString() == "no error occurred")
        {
            if ((doc.object().value("type").toString() == "connect") && (doc.object().value("status").toString() == "yes"))
            {
                QMessageBox::information(this, "Подключено", "Вы подключены к серверу");
            }
            else if (doc.object().value("type").toString() == "resultSelect")
            {
                QStandardItemModel *model = new QStandardItemModel(nullptr);
                model->setHorizontalHeaderLabels(QStringList() << "Name");

                QJsonArray docAr = doc.object().value("result").toArray();
                for (int i = 0; i < docAr.count(); i++)
                {
                    QStandardItem *col = new QStandardItem(docAr[i].toObject().value("name").toString());
                    model->appendRow(col);
                }
              ui->tableView->setModel(model);
            }
            else
            {

                QMessageBox::warning(this, "ошибка", "Нет подключения");
            }
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Ошибка в передачи данных:" + docError.errorString());
        }
            }
        }

        void MainWindow::sockDisc()
        {
            socket->deleteLater();
        }

        void MainWindow::on_pushButton_2_clicked()
        {  socket->connectToHost("192.168.0.179",1234);
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(false);

        }

        void MainWindow::on_pushButton_clicked()
        { if(socket->isOpen()){
            socket->write("{\"type\":\"select\",\"params\":\"workers\"}");
            socket->waitForBytesWritten(500);
            } else {
                QMessageBox::warning(this,"Ошибка","Соединение не было установлено");
            }

        }



