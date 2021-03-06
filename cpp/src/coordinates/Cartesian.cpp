/*
 * Cartesian.cpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#include "Cartesian.hpp"
#include "LatitudeLongitude.hpp"
#include <cmath>



namespace coordinates {

Cartesian::Cartesian(const double x,const double y,const double z) : vector(3) {
	vector(0)=x;
	vector(1)=y;
	vector(2)=z;
}

Cartesian::Cartesian(const LatitudeLongitude &l) : vector(3) {
	auto phi=l.phi();
	auto lambda=l.lambda();
	auto e=l.ellipsoid();
	
	auto c=cos(phi);
	auto s=sin(phi);
	auto nu=e.majorAxis()/sqrt(1.0-e.eccentricity1()*s*s);
	vector(0)=nu*c*cos(lambda);
	vector(1)=nu*c*sin(lambda);
	vector(2)=nu*(1.0-e.eccentricity1())*s;
}

double Cartesian::P() const {
	return hypot(vector(0),vector(1));
}

double Cartesian::RSquared() const {
	return boost::numeric::ublas::inner_prod(vector,vector);
}

double Cartesian::operator[](const Cartesian::Axis &axis) const {
	return vector(static_cast<unsigned>(axis));
}

Cartesian Cartesian::transform(const mapping::Helmert &helmert) {
	auto out=helmert.transform(vector);
	return std::move(Cartesian(out));
}




} /* namespace coordinates */

