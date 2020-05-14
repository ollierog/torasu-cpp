#ifndef STD_INCLUDE_TORASU_STD_SPOILSDR_HPP_
#define STD_INCLUDE_TORASU_STD_SPOILSDR_HPP_

//
// DataResource Spoils
//
// ~ This file spoils all DataResource-types from torasu::tstd
//

#ifdef TORASU_SPOILS_UNWRAP_ALL
	#define TORASU_SPOILS_UNWRAP_STD
#endif

namespace torasu::tstd {

class DPNum;
#ifdef TORASU_SPOILS_UNWRAP_STD
	#include <torasu/std/DPNum.hpp>
#endif

class DPString;
#ifdef TORASU_SPOILS_UNWRAP_STD
	#include <torasu/std/DPString.hpp>
#endif

class DRBImg;
#ifdef TORASU_SPOILS_UNWRAP_STD
	#include <torasu/std/DRBImg.hpp>
#endif

} // namespace torasu::tstd


#endif // STD_INCLUDE_TORASU_STD_SPOILSDR_HPP_