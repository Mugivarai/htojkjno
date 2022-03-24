#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QStandardItem>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QTcpSocket *socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
public slots:
    void sockReady();
    void sockDisc();
private slots:
void on_pushButton_2_clicked();
void on_pushButton_clicked();

private:
    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
