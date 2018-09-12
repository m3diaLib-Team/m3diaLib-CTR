#ifndef NDSP_H
#define NDSP_H

#pragma once
#include <vector>
#include "m3d/core/lock.hpp"

namespace m3d {
    namespace priv {
        namespace ndsp {
            extern m3d::Mutex channelMutex;
            extern bool initialized;
            extern std::vector<int> occupiedChannels;

            extern bool channelsFree();

            extern int find_missing(std::vector<int> t_vector, int t_number);

            extern int occupyChannel();

            extern void freeChannel(int t_id);
        } /* ndsp */
    } /* priv */
} /* m3d */


#endif /* end of include guard: NDSP_H */
