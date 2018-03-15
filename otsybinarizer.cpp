#include "otsybinarizer.h"
#include "utils.h"
#include "vector"

OtsyBinarizer::OtsyBinarizer()
{

}

void OtsyBinarizer::doFilter(QImage &image){
    int treshold = otsuThreshold(image);
    for (int h = 0 ; h < image.height() ; h++ ){
        for ( int w = 0 ; w < image.width() ; w++ ){
            if (Utils::getPixelLight(w,h,image) > treshold ){
                image.setPixelColor(w,h,QColor(WHITE,WHITE,WHITE,255));
            }else {
                image.setPixelColor(w,h,QColor(BLACK,BLACK,BLACK,255));
            }
        }
    }
}

QString *OtsyBinarizer::getDescription()
{
    QString *description = new QString("Отсу бинаризатор");
    return description;
}

int OtsyBinarizer::calculateIntensitySum(vector<int> hist)
{
    int sum = 0;
    for (int i = 0 ; i < INTENSITY_LAYER_NUMBER - 1 ; i++ ){
        sum =sum + hist.at(i)*i;
    }
    return sum;

}

vector<int> OtsyBinarizer::calculateHist(QImage &image) {
    vector<int> hist;
    hist.resize(255);
    for ( int h = 0; h < image.height(); h++) {
        for( int w = 0 ; w < image.width() ; w++ ){
            hist[Utils::getPixelLight(w,h,image)]++;
        }
    }
    return hist;
}


int OtsyBinarizer::otsuThreshold(QImage &image) {
    vector<int> hist = calculateHist(image);

    // Необходимы для быстрого пересчета разности дисперсий между классами
    int all_pixel_count = image.width()*image.height();
    int all_intensity_sum = calculateIntensitySum(hist);

    int best_thresh = 0;
    double best_sigma = 0.0;

    int first_class_pixel_count = 0;
    int first_class_intensity_sum = 0;

    // Перебираем границу между классами
    // thresh < INTENSITY_LAYER_NUMBER - 1, т.к. при 255 в ноль уходит знаменатель внутри for
    for (int thresh = 0; thresh < INTENSITY_LAYER_NUMBER - 1; ++thresh) {
        first_class_pixel_count += hist[thresh];
        first_class_intensity_sum += thresh * hist[thresh];

        double first_class_prob = first_class_pixel_count / (double) all_pixel_count;
        double second_class_prob = 1.0 - first_class_prob;

        double first_class_mean = first_class_intensity_sum / (double) first_class_pixel_count;
        double second_class_mean = (all_intensity_sum - first_class_intensity_sum)
            / (double) (all_pixel_count - first_class_pixel_count);

        double mean_delta = first_class_mean - second_class_mean;

        double sigma = first_class_prob * second_class_prob * mean_delta * mean_delta;

        if (sigma > best_sigma) {
            best_sigma = sigma;
            best_thresh = thresh;
        }
    }

   return best_thresh-20;
}
