#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QImage>
#include <array>

void gaussian_kernel(float);
void magnitude(QImage&, const QImage&, const QImage&);
QImage canny(const QImage&, float, float, float);
QImage sobel(const QImage&);
QImage prewitt(const QImage&);
QImage roberts(const QImage&);
QImage scharr(const QImage&);
QImage hysteresis(const QImage&, float, float);

template <class T>
QImage convolution(const T& kernel, const QImage& image) {
    int kw = kernel[0].size(), kh = kernel.size(),
        offsetx = kw / 2, offsety = kw / 2;
    QImage out(image.size(), image.format());
    float sum;

    quint8 *line;
    const quint8 *lookup_line;

    for (int y = 0; y < image.height(); y++) {
        line = out.scanLine(y);
        for (int x = 0; x < image.width(); x++) {
            sum = 0;

            for (int j = 0; j < kh; j++) {
                if (y + j < offsety || y + j >= image.height())
                    continue;
                lookup_line = image.constScanLine(y + j - offsety);
                for (int i = 0; i < kw; i++) {
                    if (x + i < offsetx || x + i >= image.width())
                        continue;
                    sum += kernel[j][i] * lookup_line[x + i - offsetx];
                }
            }

            line[x] = qBound(0x00, static_cast<int>(sum), 0xFF);
        }
    }

    return out;
}

#endif // ALGORITHMS_H
