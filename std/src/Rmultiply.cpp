#include "../include/torasu/std/Rmultiply.hpp"

#include <string>
#include <optional>
#include <chrono>
#include <iostream>

#include <torasu/torasu.hpp>
#include <torasu/render_tools.hpp>

#include <torasu/std/Dnum.hpp>
#include <torasu/std/Dbimg.hpp>

using namespace std;

namespace torasu::tstd {

Rmultiply::Rmultiply(Renderable* a, Renderable* b)
	: SimpleRenderable(std::string("STD::RMULTIPLY"), false, true) {
	this->a = a;
	this->b = b;
}

Rmultiply::~Rmultiply() {

}

ResultSegment* Rmultiply::renderSegment(ResultSegmentSettings* resSettings, RenderInstruction* ri) {

	if (numPipeline.compare(resSettings->getPipeline()) == 0) {

		tools::RenderInstructionBuilder rib;
		tools::RenderResultSegmentHandle<Dnum> resHandle = rib.addSegmentWithHandle<Dnum>(numPipeline, NULL);

		// Sub-Renderings
		auto ei = ri->getExecutionInterface();
		auto rctx = ri->getRenderContext();

		auto rendA = rib.enqueueRender(a, rctx, ei);
		auto rendB = rib.enqueueRender(b, rctx, ei);

		RenderResult* resA = ei->fetchRenderResult(rendA);
		RenderResult* resB = ei->fetchRenderResult(rendB);

		// Calculating Result from Results

		std::optional<double> calcResult;

		tools::CastedRenderSegmentResult<Dnum> a = resHandle.getFrom(resA);
		tools::CastedRenderSegmentResult<Dnum> b = resHandle.getFrom(resB);

		if (a.getResult()!=NULL && b.getResult()!=NULL) {
			calcResult = a.getResult()->getNum() * b.getResult()->getNum();
		}

		// Free sub-results

		delete resA;
		delete resB;

		// Saving Result

		if (calcResult.has_value()) {
			Dnum* mulRes = new Dnum(calcResult.value());
			return new ResultSegment(ResultSegmentStatus_OK, mulRes, true);
		} else {
			Dnum* errRes = new Dnum(0);
			return new ResultSegment(ResultSegmentStatus_OK_WARN, errRes, true);
		}

	} else if (visPipeline.compare(resSettings->getPipeline()) == 0) {
		Dbimg_FORMAT* fmt;
		if ( !( resSettings->getResultFormatSettings() != NULL
				&& (fmt = dynamic_cast<Dbimg_FORMAT*>(resSettings->getResultFormatSettings())) )) {
			return new ResultSegment(ResultSegmentStatus_INVALID_FORMAT);
		}

		tools::RenderInstructionBuilder rib;
		tools::RenderResultSegmentHandle<Dbimg> resHandle = rib.addSegmentWithHandle<Dbimg>(visPipeline, fmt);

		// Sub-Renderings
		auto ei = ri->getExecutionInterface();
		auto rctx = ri->getRenderContext();

		auto rendA = rib.enqueueRender(a, rctx, ei);
		auto rendB = rib.enqueueRender(b, rctx, ei);

		RenderResult* resA = ei->fetchRenderResult(rendA);
		RenderResult* resB = ei->fetchRenderResult(rendB);

		// Calculating Result from Results

		tools::CastedRenderSegmentResult<Dbimg> a = resHandle.getFrom(resA);
		tools::CastedRenderSegmentResult<Dbimg> b = resHandle.getFrom(resB);

		Dbimg* result = NULL;

		if (a.getResult()!=NULL && b.getResult()!=NULL) {

			result = new Dbimg(*fmt);

			const uint32_t height = result->getHeight();
			const uint32_t width = result->getWidth();
			const uint32_t channels = 4;
			const size_t dataSize = height*width*channels;


			uint8_t* srcA = a.getResult()->getImageData();
			uint8_t* srcB = b.getResult()->getImageData();
			uint8_t* dest = result->getImageData();

			auto benchBegin = std::chrono::steady_clock::now();

			for (size_t i = 0; i < dataSize; i++) {
				// dest[i] = (srcA[i]>>4)*(srcB[i]>>4);
				dest[i] = ((uint16_t) srcA[i]*srcB[i]) >> 8;
				// *dest++ = ((uint16_t) *srcA++ * *srcB++) >> 8;
			}

			auto benchEnd = std::chrono::steady_clock::now();
			std::cout << "  Mul Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(benchEnd - benchBegin).count() << "[ms] " << std::chrono::duration_cast<std::chrono::microseconds>(benchEnd - benchBegin).count() << "[us]" << std::endl;

		}

		delete resA;
		delete resB;

		if (result != NULL) {
			return new ResultSegment(ResultSegmentStatus_OK, result, true);
		} else {
			Dbimg* errRes = new Dbimg(*fmt);
			return new ResultSegment(ResultSegmentStatus_OK_WARN, errRes, true);
		}

	} else {
		return new ResultSegment(ResultSegmentStatus_INVALID_SEGMENT);
	}

}

map<string, Element*> Rmultiply::getElements() {
	map<string, Element*> elems;

	elems["a"] = a;
	elems["b"] = b;

	return elems;
}

void Rmultiply::setElement(std::string key, Element* elem) {
	if (torasu::tools::trySetRenderableSlot("a", &a, false, key, elem)) return;
	if (torasu::tools::trySetRenderableSlot("b", &b, false, key, elem)) return;
	throw torasu::tools::makeExceptSlotDoesntExist(key);
}

} // namespace torasu::tstd