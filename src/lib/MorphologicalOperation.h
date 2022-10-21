#pragma once

#include "Type.h"

class MorphologicalOperation {
public:
    static BinaryImg diff(BinaryImg &A, BinaryImg &B);

    static BinaryImg erosion(BinaryImg &A, BinaryTemplate &B);

    static BinaryImg dilation(BinaryImg &A, BinaryTemplate &B);

    static BinaryImg open(BinaryImg &A, BinaryTemplate &B);

    static BinaryImg close(BinaryImg &A, BinaryTemplate &B);
};