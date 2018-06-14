#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CodeEditor.h"
#include "Scanner.h"
#include "Parser.h"
#include "OStreamToTextEdit.h"
#include<fstream>
#include<iostream>
#include<functional>

#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QFileInfo>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->editorTabWidget->addTab(new CodeEditor(),"new file");

    OStreamToTextEdit* redirect = new OStreamToTextEdit(std::cerr,ui->ErrorMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_File_triggered()
{
    ui->editorTabWidget->addTab(new CodeEditor(),"new file");
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fullPath = QFileDialog::getOpenFileName(this, "Open the file");


    QFileInfo fileInfo(fullPath);
    QString filename(fileInfo.fileName());

    CodeEditor* codeEditor = new CodeEditor(fullPath);
    ui->editorTabWidget->addTab(codeEditor,filename);
	ui->editorTabWidget->setCurrentWidget(codeEditor);
}

void MainWindow::on_editorTabWidget_tabCloseRequested(int index)
{
    this->on_actionSave_triggered();
    ui->editorTabWidget->removeTab(index);
}

void MainWindow::on_actionSave_triggered()
{
    CodeEditor * curEditor = dynamic_cast<CodeEditor *>(ui->editorTabWidget->currentWidget());
    curEditor->saveToFile();
    setCurrentEditorTabTitle(curEditor->getFilePath());
}

void MainWindow::on_actionLexical_Analysis_triggered()
{
    CodeEditor * curEditor = dynamic_cast<CodeEditor *>(ui->editorTabWidget->currentWidget());
    curEditor->saveToFile();
    QString filePath = curEditor->getFilePath();
    setCurrentEditorTabTitle(filePath);
    std::ifstream* infile = new std::ifstream();
    infile->open(filePath.toStdString());
    Scanner scanner(*infile);
    ui->CompileOutput->append("Lexical Analysis result:");
    std::list<Token> tokenSequence = scanner.getTokenSequence();
    for(auto& token:tokenSequence){
        ui->CompileOutput->append(token.toString().c_str());
    }
    infile->close();
}

void MainWindow::setCurrentEditorTabTitle(QString filePath)
{
    if(!filePath.isEmpty()){
        QFileInfo fileInfo(filePath);
        QString fileName(fileInfo.fileName());
        ui->editorTabWidget->setTabText(ui->editorTabWidget->currentIndex(),fileName);
    }
}


void MainWindow::on_actionSyntax_Analysis_triggered()
{
    CodeEditor * curEditor = dynamic_cast<CodeEditor *>(ui->editorTabWidget->currentWidget());
    curEditor->saveToFile();
    QString filePath = curEditor->getFilePath();
    setCurrentEditorTabTitle(filePath);
    std::ifstream* infile = new std::ifstream();
    infile->open(filePath.toStdString());
    Scanner scanner(*infile);
    Parser parser(scanner);

    auto parseTree = parser.getParseTree();

    QString syntaxFile = filePath + ".parse";

    std::function<void(void)> printFun=[&parser,&parseTree](){
        parser.printParseTree(parseTree);
    };

    redirectStdoutToFile(std::cout,syntaxFile,printFun);

    ui->CompileOutput->append("Lexical Analysis result:");

    appendFileToTextEdit(syntaxFile,*ui->CompileOutput);

    infile->close();
    delete infile;
}

void MainWindow::redirectStdoutToFile(std::ostream & stdOutStream,QString& filePath,std::function<void(void)>& printFun)
{
    std::streambuf *psbuf, *backup;
    std::ofstream filestr;
    filestr.open (filePath.toStdString());
    backup = stdOutStream.rdbuf();
    psbuf = filestr.rdbuf();
    stdOutStream.rdbuf(psbuf);

    printFun();

    stdOutStream.rdbuf(backup);
    filestr.close();
}

void MainWindow::appendFileToTextEdit(QString& filpath,QTextEdit& textEdit)
{
    QFile file(filpath);
    if(!file.exists()){
       qDebug() << "NO existe el archivo "<<filpath;
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream stream(&file);
       while (!stream.atEnd()){
           textEdit.append(stream.readLine());
       }
    }
    file.close();
}

void MainWindow::on_actionClear_message_triggered()
{
    ui->ErrorMessage->clear();
    ui->CompileOutput->clear();
}
