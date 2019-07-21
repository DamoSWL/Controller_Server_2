/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_fileType;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_remoteIP;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *radioButton_country;
    QRadioButton *radioButton_province;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_remotePort;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_userName;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_code;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lineEdit_localPath;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_browsePath;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *lineEdit_remotePath;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButton_configConfirm;
    QPushButton *pushButton_configCancel;
    QSpacerItem *verticalSpacer;
    QTableWidget *tableWidget_FTPConfig;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_upload;
    QTableView *tableView_FTPview;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_openLog;
    QPushButton *pushButton_clearTable;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(689, 976);
        verticalLayout_3 = new QVBoxLayout(Widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(label);

        comboBox_fileType = new QComboBox(groupBox);
        comboBox_fileType->addItem(QString());
        comboBox_fileType->addItem(QString());
        comboBox_fileType->addItem(QString());
        comboBox_fileType->addItem(QString());
        comboBox_fileType->addItem(QString());
        comboBox_fileType->addItem(QString());
        comboBox_fileType->addItem(QString());
        comboBox_fileType->addItem(QString());
        comboBox_fileType->setObjectName(QStringLiteral("comboBox_fileType"));
        comboBox_fileType->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(comboBox_fileType);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(80, 0));
        label_2->setScaledContents(true);

        horizontalLayout_3->addWidget(label_2);

        lineEdit_remoteIP = new QLineEdit(groupBox);
        lineEdit_remoteIP->setObjectName(QStringLiteral("lineEdit_remoteIP"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_remoteIP->sizePolicy().hasHeightForWidth());
        lineEdit_remoteIP->setSizePolicy(sizePolicy);
        lineEdit_remoteIP->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(lineEdit_remoteIP);

        horizontalSpacer_5 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        radioButton_country = new QRadioButton(groupBox);
        radioButton_country->setObjectName(QStringLiteral("radioButton_country"));
        radioButton_country->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_country);

        radioButton_province = new QRadioButton(groupBox);
        radioButton_province->setObjectName(QStringLiteral("radioButton_province"));

        horizontalLayout_3->addWidget(radioButton_province);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(80, 0));

        horizontalLayout_2->addWidget(label_3);

        lineEdit_remotePort = new QLineEdit(groupBox);
        lineEdit_remotePort->setObjectName(QStringLiteral("lineEdit_remotePort"));
        sizePolicy.setHeightForWidth(lineEdit_remotePort->sizePolicy().hasHeightForWidth());
        lineEdit_remotePort->setSizePolicy(sizePolicy);
        lineEdit_remotePort->setMaxLength(2);
        lineEdit_remotePort->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_remotePort);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(80, 0));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_userName = new QLineEdit(groupBox);
        lineEdit_userName->setObjectName(QStringLiteral("lineEdit_userName"));
        sizePolicy.setHeightForWidth(lineEdit_userName->sizePolicy().hasHeightForWidth());
        lineEdit_userName->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(lineEdit_userName);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(label_5);

        lineEdit_code = new QLineEdit(groupBox);
        lineEdit_code->setObjectName(QStringLiteral("lineEdit_code"));
        sizePolicy.setHeightForWidth(lineEdit_code->sizePolicy().hasHeightForWidth());
        lineEdit_code->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(lineEdit_code);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(80, 0));

        horizontalLayout_6->addWidget(label_6);

        lineEdit_localPath = new QLineEdit(groupBox);
        lineEdit_localPath->setObjectName(QStringLiteral("lineEdit_localPath"));
        sizePolicy.setHeightForWidth(lineEdit_localPath->sizePolicy().hasHeightForWidth());
        lineEdit_localPath->setSizePolicy(sizePolicy);
        lineEdit_localPath->setMinimumSize(QSize(242, 0));
        lineEdit_localPath->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(lineEdit_localPath);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        pushButton_browsePath = new QPushButton(groupBox);
        pushButton_browsePath->setObjectName(QStringLiteral("pushButton_browsePath"));

        horizontalLayout_6->addWidget(pushButton_browsePath);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(80, 0));

        horizontalLayout_7->addWidget(label_7);

        lineEdit_remotePath = new QLineEdit(groupBox);
        lineEdit_remotePath->setObjectName(QStringLiteral("lineEdit_remotePath"));
        sizePolicy.setHeightForWidth(lineEdit_remotePath->sizePolicy().hasHeightForWidth());
        lineEdit_remotePath->setSizePolicy(sizePolicy);
        lineEdit_remotePath->setMinimumSize(QSize(240, 0));
        lineEdit_remotePath->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(lineEdit_remotePath);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        pushButton_configConfirm = new QPushButton(groupBox);
        pushButton_configConfirm->setObjectName(QStringLiteral("pushButton_configConfirm"));

        horizontalLayout_7->addWidget(pushButton_configConfirm);

        pushButton_configCancel = new QPushButton(groupBox);
        pushButton_configCancel->setObjectName(QStringLiteral("pushButton_configCancel"));

        horizontalLayout_7->addWidget(pushButton_configCancel);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        tableWidget_FTPConfig = new QTableWidget(groupBox);
        if (tableWidget_FTPConfig->columnCount() < 6)
            tableWidget_FTPConfig->setColumnCount(6);
        tableWidget_FTPConfig->setObjectName(QStringLiteral("tableWidget_FTPConfig"));
        tableWidget_FTPConfig->setColumnCount(6);
        tableWidget_FTPConfig->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableWidget_FTPConfig);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_9);

        pushButton_upload = new QPushButton(groupBox_2);
        pushButton_upload->setObjectName(QStringLiteral("pushButton_upload"));

        horizontalLayout_11->addWidget(pushButton_upload);


        verticalLayout_2->addLayout(horizontalLayout_11);

        tableView_FTPview = new QTableView(groupBox_2);
        tableView_FTPview->setObjectName(QStringLiteral("tableView_FTPview"));
        tableView_FTPview->horizontalHeader()->setDefaultSectionSize(180);
        tableView_FTPview->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(tableView_FTPview);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);

        pushButton_openLog = new QPushButton(groupBox_2);
        pushButton_openLog->setObjectName(QStringLiteral("pushButton_openLog"));

        horizontalLayout_10->addWidget(pushButton_openLog);

        pushButton_clearTable = new QPushButton(groupBox_2);
        pushButton_clearTable->setObjectName(QStringLiteral("pushButton_clearTable"));

        horizontalLayout_10->addWidget(pushButton_clearTable);


        verticalLayout_2->addLayout(horizontalLayout_10);


        verticalLayout_3->addWidget(groupBox_2);

        verticalLayout_3->setStretch(1, 1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QApplication::translate("Widget", "FTP\344\270\212\344\274\240\351\205\215\347\275\256", nullptr));
        label->setText(QApplication::translate("Widget", "\346\226\207\344\273\266\347\261\273\345\236\213", nullptr));
        comboBox_fileType->setItemText(0, QApplication::translate("Widget", "\345\212\237\347\216\207\350\260\261\346\226\207\344\273\266", nullptr));
        comboBox_fileType->setItemText(1, QApplication::translate("Widget", "\345\276\204\345\220\221\346\226\207\344\273\266", nullptr));
        comboBox_fileType->setItemText(2, QApplication::translate("Widget", "\345\256\236\346\227\266\346\225\260\346\215\256\346\226\207\344\273\266", nullptr));
        comboBox_fileType->setItemText(3, QApplication::translate("Widget", "\345\215\212\345\260\217\346\227\266\346\225\260\346\215\256\346\226\207\344\273\266", nullptr));
        comboBox_fileType->setItemText(4, QApplication::translate("Widget", "\344\270\200\345\260\217\346\227\266\346\225\260\346\215\256\346\226\207\344\273\266", nullptr));
        comboBox_fileType->setItemText(5, QApplication::translate("Widget", "\347\212\266\346\200\201\346\226\207\344\273\266", nullptr));
        comboBox_fileType->setItemText(6, QApplication::translate("Widget", "\346\240\207\345\256\232\346\226\207\344\273\266", nullptr));
        comboBox_fileType->setItemText(7, QApplication::translate("Widget", "\346\227\245\345\277\227\346\226\207\344\273\266", nullptr));

        label_2->setText(QApplication::translate("Widget", "\350\277\234\347\250\213IP\345\234\260\345\235\200", nullptr));
        radioButton_country->setText(QApplication::translate("Widget", "\345\233\275\345\256\266\347\272\247\345\217\260\347\253\231", nullptr));
        radioButton_province->setText(QApplication::translate("Widget", "\347\234\201\347\272\247\345\217\260\347\253\231", nullptr));
        label_3->setText(QApplication::translate("Widget", "\350\277\234\347\250\213\347\253\257\345\217\243\345\217\267", nullptr));
        lineEdit_remotePort->setText(QApplication::translate("Widget", "21", nullptr));
        label_4->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_5->setText(QApplication::translate("Widget", "\345\257\206\347\240\201", nullptr));
        label_6->setText(QApplication::translate("Widget", "\347\233\221\346\216\247\350\267\257\345\276\204", nullptr));
        pushButton_browsePath->setText(QApplication::translate("Widget", "\346\265\217\350\247\210", nullptr));
        label_7->setText(QApplication::translate("Widget", "\350\277\234\347\250\213\350\267\257\345\276\204", nullptr));
        pushButton_configConfirm->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", nullptr));
        pushButton_configCancel->setText(QApplication::translate("Widget", "\345\210\240\351\231\244", nullptr));
        groupBox_2->setTitle(QApplication::translate("Widget", "FTP\344\270\212\344\274\240", nullptr));
        pushButton_upload->setText(QApplication::translate("Widget", "\345\274\200\345\247\213", nullptr));
        pushButton_openLog->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\346\227\245\345\277\227", nullptr));
        pushButton_clearTable->setText(QApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
