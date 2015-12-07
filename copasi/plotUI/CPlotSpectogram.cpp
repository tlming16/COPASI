// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <copasi/plotUI/CPlotSpectogram.h>

#include <copasi/plotUI/CSpectorgramData.h>

CPlotSpectogram::CPlotSpectogram(QMutex *pMutex,
                                 const CPlotItem::Type &type,
                                 const COutputInterface::Activity &activity,
                                 const QString &title,
                                 bool logZ,
                                 double limitZ,
                                 bool bilinear)
  : QwtPlotSpectrogram(title)
  , mpMutex(pMutex)
  , mType(type)
  , mActivity(activity)
  , mLogZ(logZ)
  , mLimitZ(limitZ)
  , mBilinear(bilinear)
{

}

void CPlotSpectogram::setDataSize(const size_t &size)
{
#if QWT_VERSION > 0x060000

  switch (mType)
    {

      case CPlotItem::spectogram:
      {
        QwtRasterData *pData = const_cast<QwtRasterData *>(data());
        static_cast< CSpectorgramData * >(pData)->setSize(size);
        break;
      }

      default:
        fatalError();
        break;
    }

#else

  switch (mType)
    {

      case CPlotItem::spectogram:
      {
        QwtRasterData *pData = const_cast<QwtRasterData *>(&data());
        static_cast<CSpectorgramData *>(pData)->setSize(size);
        break;
      }

      default:
        fatalError();
        break;
    }

#endif
}

void CPlotSpectogram::reallocatedData(const CVector<double> *pX,
                                      const CVector<double> *pY,
                                      const CVector<double> *pZ)
{
#if QWT_VERSION > 0x060000

  switch (mType)
    {
      case CPlotItem::spectogram:
      {
        QwtRasterData *pData = const_cast<QwtRasterData *>(data());
        static_cast< CSpectorgramData * >(pData)->reallocated(pX, pY, pZ);
        break;
      }

      default:
        fatalError();
        break;
    }

#else

  switch (mType)
    {
      case CPlotItem::spectogram:
      {
        QwtRasterData *pData = const_cast<QwtRasterData *>(&data());
        static_cast<CSpectorgramData *>(pData)->reallocated(pX, pY, pZ);
        break;
      }

      default:
        fatalError();
        break;
    }

#endif
}

const CPlotItem::Type &
CPlotSpectogram::getType() const
{
  return mType;
}

const COutputInterface::Activity &
CPlotSpectogram::getActivity() const
{
  return mActivity;
}

bool
CPlotSpectogram::getLogZ() const
{
  return mLogZ;
}

void
CPlotSpectogram::setLogZ(bool logZ)
{
  mLogZ = logZ;
}

double
CPlotSpectogram::getLimitZ() const
{
  return mLimitZ;
}

void
CPlotSpectogram::setLimitZ(double limitZ)
{
  mLimitZ = limitZ;
}
bool CPlotSpectogram::getBilinear() const
{
  return mBilinear;
}

void CPlotSpectogram::setBilinear(bool bilinear)
{
  mBilinear = bilinear;
}

