#ifndef STD_INCLUDE_TORASU_STD_DBIMG_SEQUENCE_HPP_
#define STD_INCLUDE_TORASU_STD_DBIMG_SEQUENCE_HPP_

#include <utility>
#include <map>

#include <torasu/torasu.hpp>

#include <torasu/std/spoilsD.hpp>

namespace torasu::tstd {

class Dbimg_sequence : public torasu::DataResource {
private:
	double time_padding;
	std::multimap<double, torasu::tstd::Dbimg*, std::less<double>> frames;

public:
	Dbimg_sequence();
	~Dbimg_sequence();

	Dbimg* addFrame(double pts, Dbimg_FORMAT format);
	std::multimap<double, torasu::tstd::Dbimg*, std::less<double>>& getFames();

	std::string getIdent() override;
	DataDump* getData() override;
};

} // namespace torasu::tstd


#endif // STD_INCLUDE_TORASU_STD_DBIMG_SEQUENCE_HPP_
