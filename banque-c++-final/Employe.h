/*
 * Employe.h
 *
 *  Created on: 17 janv. 2017
 *      Author: joel
 */

#ifndef EMPLOYE_H_
#define EMPLOYE_H_

namespace exemple {

class Employe {
public:
	virtual ~Employe();
	virtual void travailler() = 0;
};

} /* namespace exemple */

#endif /* EMPLOYE_H_ */
