#include "base.h"

namespace ap {
    base::base(int _filteringType) {
        commandType = _filteringType;
    }

    base::~base(void) {
    }

    void base::setProcess(int _filteringType) {
        commandType = _filteringType;
    };
}   
