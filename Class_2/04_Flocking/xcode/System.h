//
//  System.h
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/18/14.
//
//

#ifndef __Flocking__System__
#define __Flocking__System__
#include "Emitter.h"
#include "Affector.h"


namespace oem {
    class System {
    public:
        System();
        virtual void setup();
        virtual void update();
        virtual void draw();
        void    addEmitter( EmitterRef emitter );
        void    addAffector( AffectorRef affector );
    };
    typedef std::shared_ptr<System> SystemRef;
}
#endif /* defined(__Flocking__System__) */
