#ifndef SANDBOXBROWSER_H
#define SANDBOXBROWSER_H

#include <QMainWindow>
#include <QX11EmbedContainer>

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

    void on_pushButton_clicked();

private:
    Ui::SandboxBrowser *ui;
};

#endif // SANDBOXBROWSER_H
