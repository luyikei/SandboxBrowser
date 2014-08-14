#ifndef SANDBOXBROWSER_H
#define SANDBOXBROWSER_H

#include <QMainWindow>
#include <QX11EmbedContainer>
#include <QList>
#include <QProcess>

namespace Ui {
class SandboxBrowser;
}

class SandboxBrowser : public QMainWindow
{
    Q_OBJECT

public:
    explicit SandboxBrowser(QWidget *parent = 0);
    ~SandboxBrowser();

private slots:

    void on_newTabButton_clicked();

    void on_terminalButton_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_newBadChild_clicked();

private:
    Ui::SandboxBrowser *ui;

    QList<QProcess*>processes;

    void startProcessInTab(const QString &executable, QStringList &arguments);
};

#endif // SANDBOXBROWSER_H
