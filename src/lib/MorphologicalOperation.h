#pragma once

#include "ImgTypes.h"

class MorphologicalOperation {
public:
    MorphologicalOperation() = delete;

    static BinaryImg diff(BinaryImg &A, BinaryImg &B);

    static BinaryImg erosion(BinaryImg &A, BinaryTemplate &B);

    static BinaryImg dilation(BinaryImg &A, BinaryTemplate &B);

    static BinaryImg open(BinaryImg &A, BinaryTemplate &B);

    static BinaryImg close(BinaryImg &A, BinaryTemplate &B);
};