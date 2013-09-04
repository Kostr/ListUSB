#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"
#include <TCHAR.H >
#include <conio.h>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ListUsbBtn_clicked()
{
    ui->textEdit->setText("<b> USB устройства </b>");
    //ui->textEdit->insertPlainText("1 - ");
    //ui->textEdit->insertPlainText("2 - ");
    //ui->textEdit->insertHtml("3 - ");
    //ui->textEdit->append("4 - ");
}

void MainWindow::on_ListComBtn_clicked()
{
    ui->textEdit->setText("<b> COM порты: </b>");
    //COM_Search();

    for (UINT i=1; i<256; i++)
       {
               char sPort[10];
               //sprintf(sPort,"\\\\.\\COM%d", i);
               sprintf(sPort,"COM%d", i);
               BOOL bSuccess = FALSE;
               HANDLE hPort = ::CreateFileA(sPort,
                                        GENERIC_READ | GENERIC_WRITE,
                                        0,
                                        0,
                                        OPEN_EXISTING,
                                        0,
                                        0);
               if(hPort == INVALID_HANDLE_VALUE)
               {
                       DWORD dwError = GetLastError();
                       if(dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
                               bSuccess = TRUE;
               }
               else
               {
                       bSuccess = TRUE;

                       #ifdef AUTO_SEARCH
                       if (Check_Connection(USB, hPort))
                       {
                           CloseHandle(hPort);
                           Form1->lComChoise->Caption = "Установлено соединение через USB";
                           i=256;
                           break;
                       }
                       else
                       {
                            hPort = ::CreateFile(sPort,
                                        GENERIC_READ | GENERIC_WRITE,
                                        0,
                                        0,
                                        OPEN_EXISTING,
                                        0,
                                        0);
                            if (Check_Connection(COM, hPort))
                            {
                               CloseHandle(hPort);
                               Form1->lComChoise->Caption = "Установлено соединение через COM";
                               i=256;
                               break;
                            }
                       }
                       #else
                       CloseHandle(hPort);
                       #endif

               } // if(hPort == INVALID_HANDLE_VALUE)

               if(bSuccess)
               {
                   ui->textEdit->append(sPort);
                       //Form1->cbPort->Items->Add(sPort);
               }
        } // for (UINT i=1; i<256; i++)
}


//---------------------------------------------------------------------------
// Поиск COM портов с помощью перебора
//---------------------------------------------------------------------------
/*
void COM_Search()
{
     //Form1->cbPort->Items->Clear();

     for (UINT i=1; i<256; i++)
        {
                char sPort[10];
                //sprintf(sPort,"\\\\.\\COM%d", i);
                sprintf(sPort,"COM%d", i);
                BOOL bSuccess = FALSE;
                HANDLE hPort = ::CreateFileA(sPort,
                                         GENERIC_READ | GENERIC_WRITE,
                                         0,
                                         0,
                                         OPEN_EXISTING,
                                         0,
                                         0);
                if(hPort == INVALID_HANDLE_VALUE)
                {
                        DWORD dwError = GetLastError();
                        if(dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
                                bSuccess = TRUE;
                }
                else
                {
                        bSuccess = TRUE;

                        #ifdef AUTO_SEARCH
                        if (Check_Connection(USB, hPort))
                        {
                            CloseHandle(hPort);
                            Form1->lComChoise->Caption = "Установлено соединение через USB";
                            i=256;
                            break;
                        }
                        else
                        {
                             hPort = ::CreateFile(sPort,
                                         GENERIC_READ | GENERIC_WRITE,
                                         0,
                                         0,
                                         OPEN_EXISTING,
                                         0,
                                         0);
                             if (Check_Connection(COM, hPort))
                             {
                                CloseHandle(hPort);
                                Form1->lComChoise->Caption = "Установлено соединение через COM";
                                i=256;
                                break;
                             }
                        }
                        #else
                        CloseHandle(hPort);
                        #endif

                } // if(hPort == INVALID_HANDLE_VALUE)

                if(bSuccess)
                {
                    ui->textEdit->append(sPort);
                        //Form1->cbPort->Items->Add(sPort);
                }
         } // for (UINT i=1; i<256; i++)
}
*/
