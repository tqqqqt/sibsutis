#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();

private:
    Ui::InfoWindow *ui;
    const QString text="Функции приложения:"
            "\n * ввод, редактирование и сохранение имён абонентов городской телефонной сети и номеров их телефонов "
            "\n * записи должны храниться и отображаться в отсортированном по именам порядке;"
            "\n * поиск по имени;"
            "\n * удаление записи;"
            "\n * очистку книги.";

private slots:
    void closeWindow();
};

#endif // INFOWINDOW_H
