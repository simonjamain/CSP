#ifndef CSP_TESTHELPER_HPP_
#define CSP_TESTHELPER_HPP_

#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"

#define FDUR_0 CSP::FiniteDuration{0}
#define DUR_0 CSP::Duration{0}

#define FDUR_3 CSP::FiniteDuration{3}
#define DUR_3 CSP::Duration{3}

#define FDUR_5 CSP::FiniteDuration{5}
#define DUR_5 CSP::Duration{5}

#define FDUR_10 CSP::FiniteDuration{10}
#define DUR_10 CSP::Duration{10}

#define FDUR_15 CSP::FiniteDuration{15}
#define DUR_15 CSP::Duration{15}

#define FDUR_20 CSP::FiniteDuration{20}
#define DUR_20 CSP::Duration{20}

#define DUR_INF CSP::Duration{CSP::PositiveInfinity{}}

#endif /* CSP_TESTHELPER_HPP_ */
