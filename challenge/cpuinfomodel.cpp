/// @file cpuinfomodel.cpp
/// @brief Qml Elements and the Tablemodel for the presentation of the cpu data
/// @author M. Gugenhan

#include "cpuinfomodel.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief qmlCpuInfoItem::qmlCpuInfoItem                                                                     ///
/// \param parent                                                                                             ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qmlCpuInfoItem::qmlCpuInfoItem(QObject *parent) : QObject(parent)
{
    m_type=myNamespace::NO_TYPE;
    m_textColor=Qt::black;
}

/// @return returns the Cpu-Information-Type of this item
myNamespace::CPUINFOTYPE qmlCpuInfoItem::type() const
{
    return m_type;
}

/// @return returns the textColor of the element
QColor qmlCpuInfoItem::textColor() const
{
    return m_textColor;
}

/// Functions sets the Cpu-Information-Type of this item
/// @param type Cpu-Information-Type for the column representation
void qmlCpuInfoItem::setType(myNamespace::CPUINFOTYPE type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}

/// Textcolor of the qml-Item
void qmlCpuInfoItem::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief cpuInfoModel::cpuInfoModel                                                                          ///
/// \param parent                                                                                              ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


cpuInfoModel::cpuInfoModel(QObject *parent) : QAbstractListModel(parent)
{
    m_cpuInfo=NULL;
    m_processorId=-1;
}

/// @return returns the cpuInfo-data
cpuInfoBase *cpuInfoModel::cpuInfo() const
{
    return m_cpuInfo;
}

/// Adds a new qmlCpuInfoItem to the internal List of the Model
/// @warning the qmlCpuInfoItem must exists all over the time, no clear object detection
void cpuInfoModel::addInfoItem(qmlCpuInfoItem *item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_qmlCpuInfoItems.append(item);
    endInsertRows();
}

/// Returns the rolenames for the model
/// The string name refers to the propertyname in the qml-delegate of the QmlListView
QHash<int, QByteArray> cpuInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ValueRole] = "value";
    roles[ColorRole] = "textColor";
    roles[TranslatedText] ="translatedText";
    return roles;
}

/// @return processorId of the model
/// the model will return the data of the selected core
short cpuInfoModel::processorId() const
{
    return m_processorId;
}

/// Sets the coreId to the model
/// the model will return the data of the selected core
/// if processorId is <0 no data will be shown
void cpuInfoModel::setProcessorId(short processorId)
{
    if (m_processorId == processorId)
        return;
    beginResetModel();
    m_processorId = processorId;
    endResetModel();
}


/// Function set the cpuInfo-data to the model
/// @warning this function has to called at least once in order for a working model
void cpuInfoModel::setCpuInfo(cpuInfoBase *cpuInfo)
{
    if (m_cpuInfo == cpuInfo)
        return;
    beginResetModel();
    m_cpuInfo = cpuInfo;
    endResetModel();
}

/// Number of Rows in the model (selected cpu-information types)
int cpuInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_qmlCpuInfoItems.size();
}

/// Returns the data for a specific row and flag
QVariant cpuInfoModel::data(const QModelIndex &index, int role) const
{
    if (role==ValueRole||role==ColorRole||role==TranslatedText) {
        if (m_cpuInfo==NULL) {
            qWarning()<<"Warning cpuInfoModel::data! Cpuinfo is NULL!";
            return QVariant();
        }
        if (m_processorId<0&&m_processorId<m_cpuInfo->numberOfProcessors()) {
            return QVariant();
        }
        if (index.row()<0 || index.row()>m_qmlCpuInfoItems.size()) {
            qWarning()<<"Warning cpuInfoModel::data! Rowcount is out of range!";
            return QVariant();
        }
        qmlCpuInfoItem* item=m_qmlCpuInfoItems[index.row()];
        if (role == ValueRole) {
            return m_cpuInfo->getValue(m_processorId,item->type());
        } else if (role == ColorRole) {
            return item->textColor();
        } else if (role==TranslatedText) {
            return m_cpuInfo->getTranslatedText(item->type());
        }
    }
    return QVariant();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief qmlCpuInfoModel::qmlCpuInfoModel                                                                   ///
/// \param parent                                                                                             ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qmlCpuInfoModelContainer::qmlCpuInfoModelContainer(QQuickItem *parent) :
    QQuickItem(parent)
{
    m_model=new cpuInfoModel(this);
}

/// Returns the cpuInfo-data of the model
QObject* qmlCpuInfoModelContainer::cpuInfo() const
{
    cpuInfoModel* infoModel=qobject_cast<cpuInfoModel*>(m_model);
    return infoModel ? infoModel->cpuInfo() : NULL;
}

/// Returns the 'real' tablemodel connected to this container
QObject *qmlCpuInfoModelContainer::model() const
{
    return m_model;
}

/// Function set the cpuInfo-data to the model
/// @warning this function has to called at least once in order for a working model
void qmlCpuInfoModelContainer::setCpuInfo(QObject *cpuInfo)
{
    cpuInfoModel* infoModel=qobject_cast<cpuInfoModel*>(m_model);
    if (infoModel) infoModel->setCpuInfo(qobject_cast<cpuInfoBase*>(cpuInfo));
    else qWarning()<<"Warning qmlCpuInfoModelContainer::setCpuInfo! cpuInfoModel is NULL!";
}

/// Set associating model of the container
void qmlCpuInfoModelContainer::setModel(QObject *model)
{
    if (m_model == model)
        return;

    m_model = model;
    emit modelChanged(model);
}

/// On component completed qmlCpuInfoItem the childs of the container will be read and added to the tableModel
void qmlCpuInfoModelContainer::componentComplete()
{
    readChilds();
}

/// Sets coreId of the shown data to the Model
void qmlCpuInfoModelContainer::setProcessorId(short arg)
{
    cpuInfoModel* infoModel=qobject_cast<cpuInfoModel*>(m_model);
    if (infoModel) infoModel->setProcessorId(arg);
    else qWarning()<<"Warning qmlCpuInfoModelContainer::setCpuCoreId! cpuInfoModel is NULL!";
}

/// Returns the core Id of the shown data
short qmlCpuInfoModelContainer::processorId() const
{
    cpuInfoModel* infoModel=qobject_cast<cpuInfoModel*>(m_model);
    return infoModel ? infoModel->processorId() : -1;
}

/// Childs of the container will be read and added to the tableModel
void qmlCpuInfoModelContainer::readChilds()
{
    QList<qmlCpuInfoItem*> modelItemList=findChildren<qmlCpuInfoItem*>();
    cpuInfoModel* infoModel=qobject_cast<cpuInfoModel*>(m_model);
    if (infoModel) {
        for (int i=0;i<modelItemList.size();i++) {
            infoModel->addInfoItem(modelItemList.at(i));
        }
    } else {
        qWarning()<<"Warning qmlCpuInfoModelContainer::readChilds! cpuInfoModel is NULL!";
    }
}









