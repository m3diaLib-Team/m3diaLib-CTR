#include <algorithm>
#include <atomic>
#include <iterator>
#include <numeric>
#include <vector>
#include "core/lock.hpp"

namespace m3d {
    namespace priv {
        namespace ndsp {
            m3d::Mutex channelMutex;
            bool initialized = false;
            std::vector<int> occupiedChannels;

            bool channelsFree() {
                m3d::Lock lock(channelMutex);
                return occupiedChannels.size() < 24;
            }

            int find_missing(std::vector<int> t_vector, int t_number) {
                std::sort(t_vector.begin(), t_vector.end());
                auto pos = std::upper_bound(t_vector.begin(), t_vector.end(), t_number);

                if (*pos - t_number > 1)
                    return t_number + 1;
                else {
                    std::vector<int> diffs;
                    std::adjacent_difference(pos, t_vector.end(), std::back_inserter(diffs));
                    auto pos2 = std::find_if(diffs.begin() + 1, diffs.end(), [](int x) { return x > 1; });
                    return *(pos + (pos2 - diffs.begin() - 1)) + 1;
                }
            }

            int occupyChannel() {
                m3d::Lock lock(channelMutex);
                if (occupiedChannels.size() == 0) {
                    occupiedChannels.push_back(0);
                    return 0;
                } else if (channelsFree()) {
                    std::sort(occupiedChannels.begin(),
                              occupiedChannels.end());
                    int channel = find_missing(occupiedChannels, -1);

                    occupiedChannels.push_back(channel);
                    return channel;
                }

                return -1;
            }

            void freeChannel(int t_id) {
                m3d::Lock lock(channelMutex);
                occupiedChannels.erase(std::remove(occupiedChannels.begin(), occupiedChannels.end(), t_id), occupiedChannels.end());
            }
        } /* ndsp */
    } /* priv */
} /* m3d */
