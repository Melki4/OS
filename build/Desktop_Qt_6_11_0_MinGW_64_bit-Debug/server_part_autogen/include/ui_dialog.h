/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QListWidget *text_output;
    QWidget *layoutWidget;
    QVBoxLayout *top_left_container;
    QHBoxLayout *horizontalLayout_2;
    QLabel *text_clients_amount;
    QSpacerItem *verticalSpacer_2;
    QLabel *text_day_progress;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *clients_amount;
    QSpacerItem *verticalSpacer;
    QProgressBar *day_progress;
    QWidget *layoutWidget1;
    QHBoxLayout *mid_container;
    QGridLayout *gridLayout;
    QLabel *barber_main;
    QLabel *text_barber_main;
    QSpacerItem *verticalSpacer_3;
    QGridLayout *gridLayout_2;
    QLabel *text_barber_brother;
    QLabel *barber_brother;
    QWidget *layoutWidget2;
    QGridLayout *bottom_container;
    QSpacerItem *verticalSpacer_4;
    QListWidget *text_logs_from_sessions;
    QVBoxLayout *verticalLayout_2;
    QComboBox *combo_box_prev_sessions;
    QPushButton *pushButton;
    QWidget *layoutWidget3;
    QVBoxLayout *top_right_container;
    QLabel *text_cash_in_hand;
    QSpacerItem *verticalSpacer_5;
    QLabel *cash_in_hand;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(1075, 597);
        Dialog->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        Dialog->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        Dialog->setSizeGripEnabled(false);
        text_output = new QListWidget(Dialog);
        new QListWidgetItem(text_output);
        new QListWidgetItem(text_output);
        text_output->setObjectName("text_output");
        text_output->setGeometry(QRect(680, 160, 357, 421));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 20, 489, 143));
        top_left_container = new QVBoxLayout(layoutWidget);
        top_left_container->setObjectName("top_left_container");
        top_left_container->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        text_clients_amount = new QLabel(layoutWidget);
        text_clients_amount->setObjectName("text_clients_amount");
        text_clients_amount->setMinimumSize(QSize(125, 30));
        text_clients_amount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(text_clients_amount);

        verticalSpacer_2 = new QSpacerItem(100, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout_2->addItem(verticalSpacer_2);

        text_day_progress = new QLabel(layoutWidget);
        text_day_progress->setObjectName("text_day_progress");
        text_day_progress->setMinimumSize(QSize(230, 30));
        text_day_progress->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        text_day_progress->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_2->addWidget(text_day_progress);


        top_left_container->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 15, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        top_left_container->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        clients_amount = new QLabel(layoutWidget);
        clients_amount->setObjectName("clients_amount");
        clients_amount->setMinimumSize(QSize(125, 40));
        clients_amount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(clients_amount);

        verticalSpacer = new QSpacerItem(100, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout->addItem(verticalSpacer);

        day_progress = new QProgressBar(layoutWidget);
        day_progress->setObjectName("day_progress");
        day_progress->setMinimumSize(QSize(230, 30));
        day_progress->setMaximumSize(QSize(230, 16777215));
        day_progress->setValue(24);

        horizontalLayout->addWidget(day_progress);


        top_left_container->addLayout(horizontalLayout);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(30, 160, 631, 243));
        mid_container = new QHBoxLayout(layoutWidget1);
        mid_container->setObjectName("mid_container");
        mid_container->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        barber_main = new QLabel(layoutWidget1);
        barber_main->setObjectName("barber_main");
        barber_main->setMaximumSize(QSize(220, 229));
        barber_main->setPixmap(QPixmap(QString::fromUtf8("../../\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270/77f02bcd-b1af-43ec-96dc-9d0dd707629b.png")));
        barber_main->setScaledContents(true);

        gridLayout->addWidget(barber_main, 0, 0, 1, 1);

        text_barber_main = new QLabel(layoutWidget1);
        text_barber_main->setObjectName("text_barber_main");
        text_barber_main->setMaximumSize(QSize(16777215, 40));

        gridLayout->addWidget(text_barber_main, 0, 1, 1, 1);


        mid_container->addLayout(gridLayout);

        verticalSpacer_3 = new QSpacerItem(40, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mid_container->addItem(verticalSpacer_3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        text_barber_brother = new QLabel(layoutWidget1);
        text_barber_brother->setObjectName("text_barber_brother");
        text_barber_brother->setMaximumSize(QSize(16777215, 40));

        gridLayout_2->addWidget(text_barber_brother, 0, 2, 1, 1);

        barber_brother = new QLabel(layoutWidget1);
        barber_brother->setObjectName("barber_brother");
        barber_brother->setPixmap(QPixmap(QString::fromUtf8("../../\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270/77f02bcd-b1af-43ec-96dc-9d0dd707629b (1).png")));
        barber_brother->setScaledContents(true);

        gridLayout_2->addWidget(barber_brother, 0, 1, 1, 1);


        mid_container->addLayout(gridLayout_2);

        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(30, 420, 621, 161));
        bottom_container = new QGridLayout(layoutWidget2);
        bottom_container->setObjectName("bottom_container");
        bottom_container->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_4 = new QSpacerItem(100, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        bottom_container->addItem(verticalSpacer_4, 0, 1, 1, 1);

        text_logs_from_sessions = new QListWidget(layoutWidget2);
        text_logs_from_sessions->setObjectName("text_logs_from_sessions");

        bottom_container->addWidget(text_logs_from_sessions, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        combo_box_prev_sessions = new QComboBox(layoutWidget2);
        combo_box_prev_sessions->setObjectName("combo_box_prev_sessions");
        combo_box_prev_sessions->setMinimumSize(QSize(150, 40));

        verticalLayout_2->addWidget(combo_box_prev_sessions);

        pushButton = new QPushButton(layoutWidget2);
        pushButton->setObjectName("pushButton");

        verticalLayout_2->addWidget(pushButton);


        bottom_container->addLayout(verticalLayout_2, 0, 2, 1, 1);

        layoutWidget3 = new QWidget(Dialog);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(740, 40, 221, 94));
        top_right_container = new QVBoxLayout(layoutWidget3);
        top_right_container->setObjectName("top_right_container");
        top_right_container->setContentsMargins(0, 0, 0, 0);
        text_cash_in_hand = new QLabel(layoutWidget3);
        text_cash_in_hand->setObjectName("text_cash_in_hand");
        text_cash_in_hand->setMinimumSize(QSize(0, 40));
        text_cash_in_hand->setAlignment(Qt::AlignmentFlag::AlignCenter);

        top_right_container->addWidget(text_cash_in_hand);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        top_right_container->addItem(verticalSpacer_5);

        cash_in_hand = new QLabel(layoutWidget3);
        cash_in_hand->setObjectName("cash_in_hand");
        cash_in_hand->setMinimumSize(QSize(0, 40));
        cash_in_hand->setAlignment(Qt::AlignmentFlag::AlignCenter);

        top_right_container->addWidget(cash_in_hand);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));

        const bool __sortingEnabled = text_output->isSortingEnabled();
        text_output->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = text_output->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("Dialog", "\320\237\320\265\321\200\320\262\320\260\321\217 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = text_output->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("Dialog", "\320\222\321\213 \321\203\321\201\320\277\320\265\321\210\320\275\320\276 \320\267\320\260\320\262\320\265\321\200\321\210\320\270\320\273\320\270 \321\200\320\260\320\261\320\276\321\202\321\203", nullptr));
        text_output->setSortingEnabled(__sortingEnabled);

        text_clients_amount->setText(QCoreApplication::translate("Dialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\272\320\273\320\270\320\265\320\275\321\202\320\276\320\262", nullptr));
        text_day_progress->setText(QCoreApplication::translate("Dialog", "\320\227\320\260\320\262\320\265\321\200\321\210\321\221\320\275\320\275\320\276\321\201\321\202\321\214 \320\264\320\275\321\217", nullptr));
        clients_amount->setText(QCoreApplication::translate("Dialog", "2", nullptr));
        barber_main->setText(QString());
        text_barber_main->setText(QCoreApplication::translate("Dialog", "TextLabel", nullptr));
        text_barber_brother->setText(QCoreApplication::translate("Dialog", "TextLabel", nullptr));
        barber_brother->setText(QString());
        pushButton->setText(QCoreApplication::translate("Dialog", "PushButton", nullptr));
        text_cash_in_hand->setText(QCoreApplication::translate("Dialog", "\320\241\321\203\320\274\320\274\320\260 \320\262 \320\272\320\260\321\201\321\201\320\265", nullptr));
        cash_in_hand->setText(QCoreApplication::translate("Dialog", "18350", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
