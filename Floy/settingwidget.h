#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
class QComboBox;
class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = 0);
    QComboBox *num_box;
    QComboBox *ng_box;
    QComboBox *maxspeed_box;
    QComboBox *bspeed_box;
    QComboBox *revdist_box;
    QComboBox *time_box;

signals:
    restartGame();
public slots:
    void on_OkBt();
    void on_ResetBt();
};

#endif // SETTINGWIDGET_H
