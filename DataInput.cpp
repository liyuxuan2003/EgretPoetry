#include "DataInput.h"
#include "ui_DataInput.h"

DataInput::DataInput(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInput)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelInfo,ui->pushButtonInfo},2);
    l1->AddUnit(new QWidget*[2]{ui->labelSource,ui->pushButtonSource},2);
    l1->AddUnit(new QWidget*[2]{ui->labelAlign,ui->pushButtonAlign},2);
    l1->AddUnit(new QWidget*[2]{ui->labelWord,ui->pushButtonWord},2);
    l1->AddUnit(new QWidget*[2]{ui->labelSent,ui->pushButtonSent},2);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonWriteData,ui->labelWriteData},2);
    l1->AddUnit(ui->labelWarning1);
    l1->AddUnit(ui->labelWarning2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonReadData,width(),height(),LiFixedCorner::RightTop);
}

DataInput::~DataInput()
{
    delete ui;
}

void DataInput::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void DataInput::Init(const QString &path,const QString &name)
{
    this->path=path;
    this->name=name;

    title="";
    author="";
    type="文";

    sentenceOrig.clear();
    sentenceTran.clear();

    partOrig.clear();
    partTran.clear();

    splitMode=SplitMode::Section;

    align.clear();

    wordInSentenceId.clear();
    wordPos.clear();
    wordMean.clear();

    sentenceId.clear();
    sentenceMean.clear();

    DisabledButton(ui->pushButtonAlign);
    DisabledButton(ui->pushButtonSent);
    DisabledButton(ui->pushButtonWord);

    ui->labelWriteData->setText("未保存数据！");
    ui->pushButtonReadData->hide();

    if(QFile(path+name+".json").size()!=0)
        ReadData(path+name+".json");
}

void DataInput::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

QString DataInput::GenerateTextOrig()
{
    QString textOrig="";
    QString splitString;

    if(splitMode==SplitMode::LineBreak)
        splitString="\n";
    if(splitMode==SplitMode::Section)
        splitString="\n\n";

    int splitCounter=0;
    for(int i=0;i<sentenceOrig.size();i++)
    {
        textOrig+=sentenceOrig[i];
        if(partOrig[splitCounter].second==i && splitCounter!=partOrig.size())
        {
            splitCounter++;
            textOrig+=splitString;
        }
    }

    return textOrig;
}

QString DataInput::GenerateTextTran()
{
    QString textTran="";
    QString splitString;

    if(splitMode==SplitMode::LineBreak)
        splitString="\n";
    if(splitMode==SplitMode::Section)
        splitString="\n\n";

    int splitCounter=0;
    for(int i=0;i<sentenceTran.size();i++)
    {
        textTran+=sentenceTran[i];
        if(partTran[splitCounter].second==i && splitCounter!=partTran.size())
        {
            splitCounter++;
            textTran+=splitString;
        }
    }

    return textTran;
}

void DataInput::EnabledButton(QPushButton* button)
{
    button->setEnabled(true);
    button->setStyleSheet("background-color:rgb(117, 133, 67); color:rgb(255,255,255)");
}

void DataInput::DisabledButton(QPushButton* button)
{
    button->setDisabled(true);
    button->setStyleSheet("background-color:rgb(106,106,106); color:rgb(255,255,255);");
}

void DataInput::on_pushButtonInfo_clicked()
{
    emit(ShowDataInputConfigInfo(title,author,type));
}

void DataInput::WrtieInfo(const QString& title,const QString& author,const QString& type)
{
    this->title=title;
    this->author=author;
    this->type=type;
}

void DataInput::on_pushButtonSource_clicked()
{
    emit(ShowDataInputConfigSource(GenerateTextOrig(),GenerateTextTran()));
}

void DataInput::WriteSource(const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,SplitMode::Mode splitMode)
{
    this->sentenceOrig=sentenceOrig;
    this->sentenceTran=sentenceTran;
    this->partOrig=partOrig;
    this->partTran=partTran;
    this->splitMode=splitMode;

    if(sentenceOrig.size()!=0)
        EnabledButton(ui->pushButtonAlign);
}

void DataInput::on_pushButtonAlign_clicked()
{
    emit(ShowDataInputConfigAlign(GenerateTextOrig(),GenerateTextTran(),sentenceOrig,sentenceTran,partOrig,partTran,align));
}

void DataInput::WriteAlign(const QList<QPair<int,int>>& align)
{
    this->align=align;

    if(align.size()==sentenceOrig.size())
    {
        EnabledButton(ui->pushButtonWord);
        EnabledButton(ui->pushButtonSent);
    }
}

void DataInput::on_pushButtonWord_clicked()
{
    emit(ShowDataInputConfigWord(GenerateTextOrig(),GenerateTextTran(),sentenceOrig,wordInSentenceId,wordPos,wordMean));
}

void DataInput::WriteWord(const QList<int>& wordInSentenceId,const QList<QPair<int,int>>& wordPos,const QStringList& wordMean)
{
    this->wordInSentenceId=wordInSentenceId;
    this->wordPos=wordPos;
    this->wordMean=wordMean;
}

void DataInput::on_pushButtonSent_clicked()
{
    emit(ShowDataInputConfigSent(GenerateTextOrig(),GenerateTextTran(),sentenceOrig,sentenceTran,align,sentenceId,sentenceMean));
}

void DataInput::WriteSent(const QList<QPair<int,int>>& sentenceId,const QStringList& sentenceMean)
{
    this->sentenceId=sentenceId;
    this->sentenceMean=sentenceMean;
}

void DataInput::on_pushButtonWriteData_clicked()
{
    QFile file(path+name+".json");
    file.open(QIODevice::ReadWrite);
    file.resize(0);

    QJsonObject jsonObjectRoot;

    //Config Info
    jsonObjectRoot.insert("title",title);
    jsonObjectRoot.insert("author",author);
    jsonObjectRoot.insert("type",type);

    //Config Source
    jsonObjectRoot.insert("sentenceOrig",QJsonArray::fromStringList(sentenceOrig));
    jsonObjectRoot.insert("sentenceTran",QJsonArray::fromStringList(sentenceTran));

    jsonObjectRoot.insert("splitMode",splitMode);

    QJsonArray jsonArrayPartOrig;
    for(int i=0;i<partOrig.size();i++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("first",partOrig[i].first);
        jsonObject.insert("second",partOrig[i].second);
        jsonArrayPartOrig.append(jsonObject);
    }
    jsonObjectRoot.insert("partOrig",jsonArrayPartOrig);

    QJsonArray jsonArrayPartTran;
    for(int i=0;i<partTran.size();i++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("first",partTran[i].first);
        jsonObject.insert("second",partTran[i].second);
        jsonArrayPartTran.append(jsonObject);
    }
    jsonObjectRoot.insert("partTran",jsonArrayPartTran);

    //Config Align
    QJsonArray jsonArrayAlign;
    for(int i=0;i<align.size();i++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("first",align[i].first);
        jsonObject.insert("second",align[i].second);
        jsonArrayAlign.append(jsonObject);
    }
    jsonObjectRoot.insert("align",jsonArrayAlign);

    //Config Word
    QJsonArray jsonArrayWordInSentenceId;
    for(int i=0;i<wordInSentenceId.size();i++)
    {
        jsonArrayWordInSentenceId.append(wordInSentenceId[i]);
    }
    jsonObjectRoot.insert("wordInSentenceId",jsonArrayWordInSentenceId);

    QJsonArray jsonArrayWordPos;
    for(int i=0;i<wordPos.size();i++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("first",wordPos[i].first);
        jsonObject.insert("second",wordPos[i].second);
        jsonArrayWordPos.append(jsonObject);
    }
    jsonObjectRoot.insert("wordPos",jsonArrayWordPos);

    jsonObjectRoot.insert("wordMean",QJsonArray::fromStringList(wordMean));

    //Config Sent
    QJsonArray jsonArraySentenceId;
    for(int i=0;i<sentenceId.size();i++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("first",sentenceId[i].first);
        jsonObject.insert("second",sentenceId[i].second);
        jsonArraySentenceId.append(jsonObject);
    }
    jsonObjectRoot.insert("sentenceId",jsonArraySentenceId);

    jsonObjectRoot.insert("sentenceMean",QJsonArray::fromStringList(sentenceMean));

    //Write Json File
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObjectRoot);

    file.write(jsonDoc.toJson());
    file.close();

    ui->labelWriteData->show();
    ui->labelWriteData->setText("保存数据成功！（"+QTime::currentTime().toString()+"）");
}

void DataInput::on_pushButtonReadData_clicked()
{
    QString readFileUrl=QFileDialog::getOpenFileName(this,"请选择需读取的诗文库（警告！当前数据将被覆盖！）","D:/","JSON File (*.json)");
    if(readFileUrl=="")
        return;
    ReadData(readFileUrl);
}

void DataInput::ReadData(QString readFileUrl)
{
    QFile file(readFileUrl);
    file.open(QIODevice::ReadOnly);

    QByteArray jsonData=file.readAll();
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
    QJsonObject jsonObjectRoot=jsonDoc.object();

    QJsonArray temp;

    //Config Info
    title=jsonObjectRoot.value("title").toString();
    author=jsonObjectRoot.value("author").toString();
    type=jsonObjectRoot.value("type").toString();

    //Config Source
    temp=jsonObjectRoot.value("sentenceOrig").toArray();
    sentenceOrig.clear();
    for(int i=0;i<temp.size();i++)
        sentenceOrig.append(temp[i].toString());

    temp=jsonObjectRoot.value("sentenceTran").toArray();
    sentenceTran.clear();
    for(int i=0;i<temp.size();i++)
        sentenceTran.append(temp[i].toString());

    temp=jsonObjectRoot.value("partOrig").toArray();
    partOrig.clear();
    for(int i=0;i<temp.size();i++)
        partOrig.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    temp=jsonObjectRoot.value("partTran").toArray();
    partTran.clear();
    for(int i=0;i<temp.size();i++)
        partTran.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    splitMode=(SplitMode::Mode)jsonObjectRoot.value("splitMode").toInt();

    //Config Align
    temp=jsonObjectRoot.value("align").toArray();
    align.clear();
    for(int i=0;i<temp.size();i++)
        align.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    //Config Word
    temp=jsonObjectRoot.value("wordInSentenceId").toArray();
    wordInSentenceId.clear();
    for(int i=0;i<temp.size();i++)
        wordInSentenceId.append(temp[i].toInt());

    temp=jsonObjectRoot.value("wordPos").toArray();
    wordPos.clear();
    for(int i=0;i<temp.size();i++)
        wordPos.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    //Config Sent
    temp=jsonObjectRoot.value("wordMean").toArray();
    wordMean.clear();
    for(int i=0;i<temp.size();i++)
        wordMean.append(temp[i].toString());

    temp=jsonObjectRoot.value("sentenceId").toArray();
    sentenceId.clear();
    for(int i=0;i<temp.size();i++)
        sentenceId.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    temp=jsonObjectRoot.value("sentenceMean").toArray();
    sentenceMean.clear();
    for(int i=0;i<temp.size();i++)
        sentenceMean.append(temp[i].toString());

    //Other
    DisabledButton(ui->pushButtonAlign);
    DisabledButton(ui->pushButtonWord);
    DisabledButton(ui->pushButtonSent);
    if(sentenceOrig.size()!=0)
    {
        EnabledButton(ui->pushButtonAlign);
        if(align.size()==sentenceOrig.size())
        {
            EnabledButton(ui->pushButtonWord);
            EnabledButton(ui->pushButtonSent);
        }
    }
}
