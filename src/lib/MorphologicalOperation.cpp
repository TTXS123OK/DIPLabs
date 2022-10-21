#include <cassert>

#include "MorphologicalOperation.h"

BinaryImg MorphologicalOperation::diff(BinaryImg &A, BinaryImg &B) {
    int aHeight = A.size();
    int aWidth = A[0].size();
    int bHeight = B.size();
    int bWidth = B[0].size();

    assert(aHeight == bHeight && aWidth == bWidth);

    BinaryImg res(aHeight, BinaryLine(aWidth, 0xff)); // init to white
    for (int i = 0; i < aHeight; i++) {
        for (int j = 0; j < aWidth; j++) {
            if (A[i][j] == 0 && B[i][j] == 0xff)
                res[i][j] = 0x00;
        }
    }

    return res;
}

BinaryImg MorphologicalOperation::erosion(BinaryImg &A, BinaryTemplate &B) {
    int aHeight = A.size();
    int aWidth = A[0].size();

    int bHeight = B.size();
    int bWidth = B[0].size();
    assert(bHeight % 2 == 1 && bWidth % 2 == 1);
    int bCenterX = bWidth / 2;
    int bCenterY = bHeight / 2;
    std::vector<std::pair<int, int>> related_points_set;
    for (int i = -bCenterY; i <= bCenterY; i++) {
        for (int j = -bCenterX; j <= bCenterX; j++) {
            if (B[bCenterY + i][bCenterX + j] == 1)
                related_points_set.emplace_back(i, j);
        }
    }

    BinaryImg res(aHeight, BinaryLine(aWidth, 0)); // init to black
    for (int i = 0; i < aHeight; i++) {
        for (int j = 0; j < aWidth; j++) {
            // if not all black, change to white
            for (auto &p: related_points_set) {
                if (0 <= i + p.second && i + p.second < aHeight
                    && 0 <= j + p.first && j + p.first < aWidth
                    && A[i + p.second][j + p.first] != 0) {
                    res[i][j] = 0xff;
                    break;
                }
            }
        }
    }
    return res;
}

BinaryImg MorphologicalOperation::dilation(BinaryImg &A, BinaryTemplate &B) {
    int aHeight = A.size();
    int aWidth = A[0].size();

    int bHeight = B.size();
    int bWidth = B[0].size();
    assert(bHeight % 2 == 1 && bWidth % 2 == 1);
    int bCenterX = bWidth / 2;
    int bCenterY = bHeight / 2;
    std::vector<std::pair<int, int>> related_points_set;
    for (int i = -bCenterY; i <= bCenterY; i++) {
        for (int j = -bCenterX; j <= bCenterX; j++) {
            if (B[bCenterY + i][bCenterX + j] == 1)
                related_points_set.emplace_back(i, j);
        }
    }

    BinaryImg res(aHeight, BinaryLine(aWidth, 0xff)); // init to white
    for (int i = 0; i < aHeight; i++) {
        for (int j = 0; j < aWidth; j++) {
            // if exist black, change to black
            for (auto &p: related_points_set) {
                if (0 <= i + p.second && i + p.second < aHeight
                    && 0 <= j + p.first && j + p.first < aWidth
                    && A[i + p.second][j + p.first] == 0) {
                    res[i][j] = 0x00;
                    break;
                }
            }
        }
    }
    return res;
}

BinaryImg MorphologicalOperation::open(BinaryImg &A, BinaryTemplate &B) {
    BinaryImg after_erosion = erosion(A, B);
    return dilation(after_erosion, B);
}

BinaryImg MorphologicalOperation::close(BinaryImg &A, BinaryTemplate &B) {
    BinaryImg after_dilation = dilation(A, B);
    return erosion(after_dilation, B);
}