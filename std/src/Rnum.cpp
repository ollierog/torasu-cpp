#include "../include/torasu/std/Rnum.hpp"

#include <string>

#include <torasu/torasu.hpp>
#include <torasu/DataPackable.hpp>

#include <torasu/std/Dnum.hpp>

using namespace std;

namespace torasu::tstd {

Rnum::Rnum(double val) : SimpleRenderable("STD::RNUM", true, false) {
	valdr = new Dnum(val);
}

Rnum::~Rnum() {
	delete valdr;
}

DataResource* Rnum::getData() {
	return valdr;
}

void Rnum::setData(DataResource* data) {
	if (Dnum* dpnum = dynamic_cast<Dnum*>(data)) {
		delete valdr;
		valdr = dpnum;
	} else {
		throw invalid_argument("The data-type \"DPNum\" is only allowed");
	}
}

ResultSegment* Rnum::renderSegment(ResultSegmentSettings* resSettings, RenderInstruction* ri) {

	if (resSettings->getPipeline().compare(pipeline) == 0) {
		return new ResultSegment(ResultSegmentStatus_OK, valdr, false);
	} else {
		return new ResultSegment(ResultSegmentStatus_INVALID_SEGMENT);
	}

}

} // namespace torasu::tstd
