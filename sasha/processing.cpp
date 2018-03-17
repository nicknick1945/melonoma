#include "processing.h"

Processing::Processing()
{

}

void Processing::median(ImageMatrix &matrix)
{
    ImageMatrix copy(matrix);
    int rows = matrix.rows();
    int cols = matrix.cols();
    int radius = 2, xn, yn;
    for (int x=radius; x<rows-radius; ++x)
        for (int y=radius; y<cols-radius; ++y)
        {
                QVector<int> vect;
                for (int i=-radius; i<=radius; ++i)
                    for (int j=-radius; j<=radius; ++j)
                    {
                        xn = x+i; yn = y+j;
                        vect.append(copy.get(xn,yn));
                    }
                std::sort(vect.begin(), vect.end());
                matrix.set(vect.at(vect.size()/2),x,y);
        }
}

void Processing::bilateral(ImageMatrix &matrix, int radius, int sigmaD, int sigmaI)
{
    ImageMatrix copy(matrix);
    int rows = matrix.rows();
    int cols = matrix.cols();
    for (int x=radius;x<rows-radius;++x)
        for (int y=radius;y<cols-radius;++y)
        {
            double I = copy.get(x,y);
            double intens = 0, weight=0;
            for(int i=-radius;i<=radius;++i) for(int j=-radius;j<=radius;++j)
            {
                int xn=x+i; int yn=y+j;
                double tw = exp(-((i*i+j*j)/(2*sigmaD*sigmaD))-
                                ((copy.get(xn,yn)-I)*(copy.get(xn,yn)-I)/(2*sigmaI*sigmaI)));
                weight+=tw;
                intens += copy.get(xn,yn)*tw;
            }
            matrix.set(intens/weight,x,y);
        }
}

void Processing::otsu(ImageMatrix &matrix)
{
    int rows = matrix.rows();
    int cols = matrix.cols();
    int hist[256];
    int sum=0;
    for (int i=0; i<256; ++i)
            hist[i]=0;
    for (int i=0; i<rows; ++i)
        for (int j=0;j<cols;++j)
            ++hist[int(matrix.get(i,j))];
    for (int i=0; i<rows; ++i)
        for (int j=0;j<cols;++j)
            sum += matrix.get(i,j);

    int all_pixel_count = rows*cols;
    int all_intensity_sum = sum;

    int best_thresh = 0;
    double best_sigma = 0.0;

    int first_class_pixel_count = 0;
    int first_class_intensity_sum = 0;

    for (int thresh = 0; thresh < 255; ++thresh)
    {
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

    for (int i=0; i<rows; ++i)
        for (int j=0; j<cols; ++j)
            matrix.set(matrix.get(i,j)<best_thresh?0:255,i,j);
}

void Processing::erosion(ImageMatrix &matrix, int radius)
{
    ImageMatrix tmp (matrix);
    int rows = matrix.rows();
    int cols = matrix.cols();
    int xn, yn;
    for (int x=radius; x<rows-radius; ++x)
        for (int y=radius; y<cols-radius; ++y)
        {
                int b = 1;
                for (int i=-radius; i<=radius; ++i)
                    for (int j=-radius; j<=radius; ++j)
                        if (i!=j)
                        {
                            xn = x+i; yn = y+j;
                            if (true && (tmp.get(xn,yn) < b))
                                b = tmp.get(xn,yn);
                        }
                matrix.set(b,x,y);
        }
}

void Processing::dilatation(ImageMatrix &matrix, int radius)
{
    ImageMatrix tmp (matrix);
    int rows = matrix.rows();
    int cols = matrix.cols();
    int xn, yn;
    for (int x=radius; x<rows-radius; ++x)
        for (int y=radius; y<cols-radius; ++y)
        {
                int b = 0;
                for (int i=-radius; i<=radius; ++i)
                    for (int j=-radius; j<=radius; ++j)
                    {
                        xn = x+i; yn = y+j;
                        if (true && tmp.get(xn,yn) > b)
                            b = tmp.get(xn,yn);
                    }
                matrix.set(b,x,y);
        }
}

void Processing::my_filter(ImageMatrix &matrix)
{
    int v_matrix[13][13] = { {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
                             {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8} };

    int h_matrix[13][13] = { {8,8,8,8,8,8,8,8,8,8,8,8,8},
                             {4,4,4,4,4,4,4,4,4,4,4,4,4},
                             {2,2,2,2,2,2,2,2,2,2,2,2,2},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                             {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
                             {-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24},
                             {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
                             {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {2,2,2,2,2,2,2,2,2,2,2,2,2},
                             {4,4,4,4,4,4,4,4,4,4,4,4,4},
                             {8,8,8,8,8,8,8,8,8,8,8,8,8} };

    int r_matrix[13][13] = {{79,32,16,12,8,4,2,1,-1,-2,-4,-8,-24},
                            {32,16,12,8,4,2,1,-1,-2,-4,-8,-24,-8},
                            {16,12,8,4,2,1,-1,-2,-4,-8,-24,-8,-4},
                            {12,8,4,2,1,-1,-2,-4,-8,-24,-8,-4,-2},
                            {8,4,2,1,-1,-2,-4,-8,-24,-8,-4,-2,-1},
                            {4,2,1,-1,-2,-4,-8,-24,-8,-4,-2,-1,1},
                            {2,1,-1,-2,-4,-8,-24,-8,-4,-2,-1,1,2},
                            {1,-1,-2,-4,-8,-24,-8,-4,-2,-1,1,2,4},
                            {-1,-2,-4,-8,-24,-8,-4,-2,-1,1,2,4,8},
                            {-2,-4,-8,-24,-8,-4,-2,-1,1,2,4,8,12},
                            {-4,-8,-24,-8,-4,-2,-1,1,2,4,8,12,16},
                            {-8,-24,-8,-4,-2,-1,1,2,4,8,12,16,32},
                            {-24,-8,-4,-2,-1,1,2,4,8,12,16,32,79} };

    int l_matrix[13][13] = { {-24,-8,-4,-2,-1,1,2,4,8,12,16,32,79},
                             {-8,-24,-8,-4,-2,-1,1,2,4,8,12,16,32},
                             {-4,-8,-24,-8,-4,-2,-1,1,2,4,8,12,16},
                             {-2,-4,-8,-24,-8,-4,-2,-1,1,2,4,8,12},
                             {-1,-2,-4,-8,-24,-8,-4,-2,-1,1,2,4,8},
                             {1,-1,-2,-4,-8,-24,-8,-4,-2,-1,1,2,4},
                             {2,1,-1,-2,-4,-8,-24,-8,-4,-2,-1,1,2},
                             {4,2,1,-1,-2,-4,-8,-24,-8,-4,-2,-1,1},
                             {8,4,2,1,-1,-2,-4,-8,-24,-8,-4,-2,-1},
                             {12,8,4,2,1,-1,-2,-4,-8,-24,-8,-4,-2},
                             {16,12,8,4,2,1,-1,-2,-4,-8,-24,-8,-4},
                             {32,16,12,8,4,2,1,-1,-2,-4,-8,-24,-8},
                             {79,32,16,12,8,4,2,1,-1,-2,-4,-8,-24} };

//    int r_matrix[13][13] = {{8,8,8,8,8,8,8,4,2,1,-1,-2,-24},
//                            {8,4,4,4,4,4,4,2,1,-1,-2,-24,-2},
//                            {8,4,2,2,2,2,2,1,-1,-2,-24,-2,-1},
//                            {8,4,2,1,1,1,1,-1,-2,-24,-2,-1,1},
//                            {8,4,2,1,-1,-1,-1,-2,-24,-2,-1,1,2},
//                            {8,4,2,1,-1,-2,-2,-24,-2,-1,1,2,4},
//                            {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
//                            {4,2,1,-1,-2,-24,-2,-2,-1,1,2,4,8},
//                            {2,1,-1,-2,-24,-2,-1,-1,-1,1,2,4,8},
//                            {1,-1,-2,-24,-2,-1,1,1,1,1,2,4,8},
//                            {-1,-2,-24,-2,-1,1,2,2,2,2,2,4,8},
//                            {-2,-24,-2,-1,1,2,4,4,4,4,4,4,8},
//                            {-24,-2,-1,1,2,4,8,8,8,8,8,8,8} };

//    int l_matrix[13][13] = {{-24,-2,-1,1,2,4,8,8,8,8,8,8,8},
//                            {-2,-24,-2,-1,1,2,4,4,4,4,4,4,8},
//                            {-1,-2,-24,-2,-1,1,2,2,2,2,2,4,8},
//                            {1,-1,-2,-24,-2,-1,1,1,1,1,2,4,8},
//                            {2,1,-1,-2,-24,-2,-1,-1,-1,1,2,4,8},
//                            {4,2,1,-1,-2,-24,-2,-2,-1,1,2,4,8},
//                            {8,4,2,1,-1,-2,-24,-2,-1,1,2,4,8},
//                            {8,4,2,1,-1,-2,-2,-24,-2,-1,1,2,4},
//                            {8,4,2,1,-1,-1,-1,-2,-24,-2,-1,1,2},
//                            {8,4,2,1,1,1,1,-1,-2,-24,-2,-1,1},
//                            {8,4,2,2,2,2,2,1,-1,-2,-24,-2,-1},
//                            {8,4,4,4,4,4,4,2,1,-1,-2,-24,-2},
//                            {8,8,8,8,8,8,8,4,2,1,-1,-2,-24} };

    int rows = matrix.rows();
    int cols = matrix.cols();
    int radius = 6, xn, yn;
    int v,h,r,l, max_effect, min_effect, difference;
    ImageMatrix tmp (matrix);
    ImageMatrix tmp_2 (matrix);

    for (int x=radius; x<rows-radius; ++x)
        for (int y=radius; y<cols-radius; ++y)
        {
            v=0;h=0;r=0;l=0;
            for (int i=-radius; i<=radius; ++i)
                for (int j=-radius; j<=radius; ++j)
                {
                    xn = x+i; yn = y+j;
                    v += tmp.get(xn,yn) * v_matrix[i+radius][j+radius];
                    h += tmp.get(xn,yn) * h_matrix[i+radius][j+radius];
                    r += tmp.get(xn,yn) * r_matrix[i+radius][j+radius];
                    l += tmp.get(xn,yn) * l_matrix[i+radius][j+radius];
                }
//            v = std::max(v,0);
//            h = std::max(h,0);
//            r = std::max(r,0);
//            l = std::max(l,0);
//            max_effect = std::max(std::max(v,h), std::max(r,l));
//            min_effect = std::min(std::min(v,h), std::min(r,l));
            max_effect = std::max(v,h);
//            min_effect = std::min(v,h);
//            difference = max_effect - min_effect;

            matrix.set(max_effect, x,y);
//            tmp_2.set(difference,x,y);
        }
    matrix.scale(0,255);
//    tmp_2.scale(0,255);
    otsu(matrix);
//    otsu(tmp_2);
    matrix.scale(0,1);
//    tmp_2.scale(0,1);
//    for (int x=0;x<rows;++x) for(int y=0;y<cols;++y)
//        matrix.set(int(matrix.get(x,y) && tmp_2.get(x,y)),x,y);


    dilatation(matrix,1);
    erosion(matrix,1);
    erosion(matrix,1);
    erosion(matrix,1);
    matrix.scale(0,255);
}

void Processing::my_filter_2(ImageMatrix &matrix)
{
    int mask [21] = {8,6,4,2,1,0,-1,-2,-4,-6,-16,-6,-4,-2,-1,0,1,2,4,6,8};
    int rows = matrix.rows();
    int cols = matrix.cols();
    int radius = 10, xn, yn;
    int v,h;
    ImageMatrix tmp (matrix);

    for (int x=radius; x<rows-radius; ++x)
        for (int y=radius; y<cols-radius; ++y)
        {
            v=0;h=0;
            for (int i=-radius; i<=radius; ++i)
                for (int j=-radius; j<=radius; ++j)
                {
                    xn = x+i; yn = y+j;
                    v += tmp.get(x,yn) * mask[j+radius];
                    h += tmp.get(xn,y) * mask[i+radius];
                }
            v = std::max(v,0);
            h = std::max(h,0);
            matrix.set(std::max(v,h), x,y);
            matrix.set(v, x,y);
        }
    matrix.scale(0,255);
    otsu(matrix);
}

void Processing::counting(ImageMatrix &matrix, int max_size, QImage &orig)
{
    std::deque<QPoint> Q;
    std::deque < std::deque<QPoint> > segments;
    matrix.scale(0,1);
    for(int x=0;x<matrix.rows();++x)
        for(int y=0;y<matrix.cols();++y)
            matrix.set(matrix.get(x,y)-2,x,y);
    for(int x=0;x<matrix.rows();++x)
        for(int y=0;y<matrix.cols();++y)
        {
            if (Q.size() != 0)
                Q.clear();
            if (matrix.get(x,y) == -1)
            {
                Q.push_back({x,y});
                int count=0;
                while(count < Q.size())
                {
                    int xn = (*(Q.begin()+count)).x();
                    int yn = (*(Q.begin()+count)).y();
                    std::vector<QPoint> neigh {{xn, yn-1},{xn-1, yn},{xn+1, yn},{xn, yn+1}};
                    for (QPoint p:neigh)
                    {
                        if (p.x()>0 && p.x()<matrix.rows() && p.y()>0 && p.y()<matrix.cols() &&
                                matrix.get(p.x(),p.y()) == -1)
                            if(std::count(Q.begin(), Q.end(), p)==0)
                                Q.push_back(p);
                    }
                    ++count;
//                    if (Q.size() > 2*max_size)
//                    {
//                        count = Q.size();
//                    }
                }
                if(count>max_size)
                {
                    for (QPoint p:Q)
                        matrix.set(0, p.x(), p.y());
                    segments.push_back(Q);
                }
                if ((count+1)<=max_size)
                {
                    for (QPoint p:Q)
                        matrix.set(-2, p.x(), p.y());
                }
            }
        }
    matrix.scale(0,1);

    int mean = 0;
    for (std::deque<QPoint> d:segments)
    {
        int sum=0, col=0;
        for (QPoint p:d)
        {
            col+=(orig.pixelColor(p.y(), p.x()).red()+orig.pixelColor(p.y(), p.x()).green()+orig.pixelColor(p.y(), p.x()).blue())/3;
            ++sum;
        }
        col/=sum;
        mean+=col;
    }
    mean/=segments.size();
    for (std::deque<QPoint> d:segments)
    {
        int sum=0, col=0;
        for (QPoint p:d)
        {
            col+=(orig.pixelColor(p.y(), p.x()).red()+orig.pixelColor(p.y(), p.x()).green()+orig.pixelColor(p.y(), p.x()).blue())/3;
            ++sum;
        }
        col/=sum;
        if (col>mean+15)
            for (QPoint p:d)
                matrix.set(0,p.x(),p.y());
    }

    matrix.scale(0,255);
}

void Processing::laplace(ImageMatrix &matrix)
{
    matrix.scale(0,1);
    int rows = matrix.rows();
    int cols = matrix.cols();
    int radius = 1, xn, yn, t;
    ImageMatrix tmp (matrix);
    int G[3][3] = { {0,1,0},
                    {1,-4,1},
                    {0,1,0} };

    for (int x=radius; x<rows-radius; ++x)
        for (int y=radius; y<cols-radius; ++y)
        {
            t=0;
            for (int i=-radius; i<=radius; ++i)
                for (int j=-radius; j<=radius; ++j)
                {
                    xn = x+i; yn = y+j;
                    t += tmp.get(xn,yn) * G[i+radius][j+radius];
                }
            matrix.set( (t==0)?0:1 ,x,y);
        }
    matrix.scale(0,255);
}

void Processing::inverse(ImageMatrix &matrix)
{
    otsu(matrix);
    matrix.scale(0,1);
    for (int i=15;i<matrix.rows()-15;++i)
        for (int j=15;j<matrix.cols()-15;++j)
            if (matrix.get(i,j) == 0)
                matrix.set(1,i,j);
    else if (matrix.get(i,j) == 1)
                matrix.set(0,i,j);
    matrix.scale(0,255);
}

void Processing::histogram(QImage &orig, ImageMatrix &matrix)
{
    std::vector<int> hist;
    hist.resize(256);
    for (int i=0;i<matrix.rows();++i)
        for (int j=0;j<matrix.cols();++j)
            if (matrix.get(i,j) != 0)
                ++hist[orig.pixelColor(j,i).red()];
    int i=0, sum = 0, tmp = 0;
    for (int a:hist)
    {
        qDebug() << i << a;
        tmp+=i*a;
        sum+=a;
        ++i;
    }
    tmp/=sum;
    qDebug() << tmp;

    for (int i=0;i<matrix.rows();++i)
        for (int j=0;j<matrix.cols();++j)
            if (matrix.get(i,j) != 0)
            {
                int col = orig.pixelColor(j,i).red();
                if (col<tmp/2)
                    matrix.set(0,i,j);
            }
}
