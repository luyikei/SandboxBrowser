#include "sandboxbrowser.h"
#include "ui_sandboxbrowser.h"

#include <QProcess>

#include <QX11EmbedWidget>
#include <QVBoxLayout>
#include <QtGui>

#include "sandboxprocess.h"


SandboxBrowser::SandboxBrowser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SandboxBrowser)
{
    ui->setupUi(this);



}

SandboxBrowser::~SandboxBrowser()
{
    delete ui;
}

void SandboxBrowser::on_newTabButton_clicked()
{


    QX11EmbedContainer *container = new QX11EmbedContainer(ui->tabWidget);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setMinimumSize(600, 600);
    ui->tabWidget->addTab(container, "test");

    QProcess* process = new QProcess(container);
    QString executable("../build-SandboxBrowserChildProcess-Qt_4-Debug/SandboxBrowserChildProcess");
    QStringList arguments;
    arguments << QString::number(container->winId());
    process->start(executable, arguments);
    qDebug() << process->pid();
}

void SandboxBrowser::on_terminalButton_clicked()
{
    QX11EmbedContainer *container = new QX11EmbedContainer(ui->tabWidget);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setMinimumSize(600, 600);
    ui->tabWidget->addTab(container, "test");

    SandBoxProcess* process = new SandBoxProcess(container);
    QString executable("xterm");
    QStringList arguments;
    arguments << "-into";
    arguments << QString::number(container->winId());
    process->start(executable, arguments);
    qDebug() << process->pid();

}
