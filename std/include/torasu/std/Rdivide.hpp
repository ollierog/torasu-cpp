#ifndef STD_INCLUDE_TORASU_STD_RDIVIDE_HPP_
#define STD_INCLUDE_TORASU_STD_RDIVIDE_HPP_

#include <string>

#include <torasu/torasu.hpp>
#include <torasu/SimpleRenderable.hpp>

#include <torasu/std/pipeline_names.hpp>
#include <torasu/std/spoilsD.hpp>

namespace torasu::tstd {

class Rdivide : public tools::SimpleRenderable {
private:
	const std::string numPipeline = std::string(TORASU_STD_PL_NUM);
	const std::string visPipeline = std::string(TORASU_STD_PL_VIS);

	Renderable* a = NULL;
	Renderable* b = NULL;

protected:
	ResultSegment* renderSegment(ResultSegmentSettings* resSettings, RenderInstruction* ri) override;

public:
	Rdivide(Renderable* a, Renderable* b);
	~Rdivide();

	torasu::ElementMap getElements() override;
	void setElement(std::string key, Element* elem) override;
};

} // namespace torasu::tstd

#endif // STD_INCLUDE_TORASU_STD_RDIVIDE_HPP_
