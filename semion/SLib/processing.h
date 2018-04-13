#ifndef PROCESSING_H
#define PROCESSING_H

/*!
 * \defgroup Processing Модуль предобработки "Processing"
 * \brief Данный модуль содержит ряд алгоритмов предобработки на полутоновых изображениях.
 * \details Все классы модуля строятся по следующей схеме:
 * - Отнаследованны от sprocessing.
 * - Имеют метод bypass для обхода(обработки) изображения. Метод не меняет оригинальное изображение,
 * т.е возвращает его преобразованную копию.
 * - Несколько методов могут собираться в конвеер SConveyor.
 */
#include "Processing/sprocessing.h"
#include "Processing/sconveyor.h"
#include "Processing/sbilateralfilter.h"
#include "Processing/sedgedetection.h"
#include "Processing/sgaussfilter.h"
#include "Processing/slaplaceoperator.h"
#include "Processing/ssquaremask.h"
#include "Processing/sthreshold.h"

#endif // PROCESSING_H
