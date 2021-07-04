#include "mac_grid.h"


#undef max
#undef min 

#define theRenderMode CUBES

bool MACGrid::theDisplayVel = false;//true


MACGrid::MACGrid()
{
    initialize();
    cout<<sphereC<<endl;

}

MACGrid::MACGrid(const MACGrid& orig)
{
   mU = orig.mU;
   mV = orig.mV;
   mW = orig.mW;
   mP = orig.mP;
   mD = orig.mD;
   mT = orig.mT;
}

MACGrid& MACGrid::operator=(const MACGrid& orig)
{
   if (&orig == this)
   {
      return *this;
   }

   mU = orig.mU;
   mV = orig.mV;
   mW = orig.mW;
   mP = orig.mP;
   mD = orig.mD;
   mT = orig.mT;   

   return *this;
}

MACGrid::~MACGrid() {}

void MACGrid::reset()
{
   mU.initialize();
   mV.initialize();
   mW.initialize();
   mP.initialize();
   mD.initialize();
   mT.initialize(0.0);
}

void MACGrid::initialize()
{
   reset();
}

vec3 MACGrid::getVelocity(const vec3& pt)
{
   vec3 vel;
    vec3 centr(sphereC[0],sphereC[1],sphereC[2]);
    centr*=theCellSize;
    double radius=Distance(centr,pt);
    if(allowsphere == 0)
    {
        vel[0] = getVelocityX(pt);
        vel[1] = getVelocityY(pt);
        vel[2] = getVelocityZ(pt);
        return vel;
    }
    else
    {
        if (radius > rr2) {
            vel[0] = getVelocityX(pt);
            vel[1] = getVelocityY(pt);
            vel[2] = getVelocityZ(pt);
            return vel;
        } else if (radius <= rr2) {
            vec3 curvel(mU.interpolate(pt), mV.interpolate(pt), mW.interpolate(pt));
            vec3 pro = Dot(curvel, (pt - centr)) * (pt - centr).Normalize();
            return (curvel - pro);
            //return -curvel;
        } 
    }
}

double MACGrid::getVelocityX(const vec3& pt)
{
   return mU.interpolate(pt);
}

double MACGrid::getVelocityY(const vec3& pt)
{
   return mV.interpolate(pt);
}

double MACGrid::getVelocityZ(const vec3& pt)
{
   return mW.interpolate(pt);
}

double MACGrid::getTemperature(const vec3& pt)
{
   return mT.interpolate(pt);
}

double MACGrid::getDensity(const vec3& pt)
{
   return mD.interpolate(pt);
}

vec3 MACGrid::getCenter(int i, int j, int k)
{
   double xstart = theCellSize/2.0;
   double ystart = theCellSize/2.0;
   double zstart = theCellSize/2.0;

   double x = xstart + i*theCellSize;
   double y = ystart + j*theCellSize;
   double z = zstart + k*theCellSize;
   return vec3(x, y, z);
}


vec3 MACGrid::getRewoundPosition(const vec3 & currentPosition, const double dt) {

	/*
	// EULER (RK1):
	vec3 currentVelocity = getVelocity(currentPosition);
	vec3 rewoundPosition = currentPosition - currentVelocity * dt;
	vec3 clippedRewoundPosition = clipToGrid(rewoundPosition, currentPosition);
	return clippedRewoundPosition;
	*/

	// HEUN / MODIFIED EULER (RK2):
	vec3 currentVelocity = getVelocity(currentPosition);
	vec3 rewoundPosition = currentPosition - currentVelocity * dt;
	vec3 clippedRewoundPosition = clipToGrid(rewoundPosition, currentPosition);
	// Keep going...
	vec3 rewoundVelocity = getVelocity(clippedRewoundPosition);
	vec3 averageVelocity = (currentVelocity + rewoundVelocity) / 2.0;
	vec3 betterRewoundPosition = currentPosition - averageVelocity * dt;
	vec3 clippedBetterRewoundPosition = clipToGrid(betterRewoundPosition, currentPosition);
	return clippedBetterRewoundPosition;
}


vec3 MACGrid::clipToGrid(const vec3& outsidePoint, const vec3& insidePoint) {
	/*
	// OLD:
	vec3 rewindPosition = outsidePoint;
	if (rewindPosition[0] < 0) rewindPosition[0] = 0; // TEMP!
	if (rewindPosition[1] < 0) rewindPosition[1] = 0; // TEMP!
	if (rewindPosition[2] < 0) rewindPosition[2] = 0; // TEMP!
	if (rewindPosition[0] > theDim[MACGrid::X]) rewindPosition[0] = theDim[MACGrid::X]; // TEMP!
	if (rewindPosition[1] > theDim[MACGrid::Y]) rewindPosition[1] = theDim[MACGrid::Y]; // TEMP!
	if (rewindPosition[2] > theDim[MACGrid::Z]) rewindPosition[2] = theDim[MACGrid::Z]; // TEMP!
	return rewindPosition;
	*/

	vec3 clippedPoint = outsidePoint;

	for (int i = 0; i < 3; i++) {
		if (clippedPoint[i] < 0) {
			vec3 distance = clippedPoint - insidePoint;
			double newDistanceI = 0 - insidePoint[i];
			double ratio = newDistanceI / distance[i];
			clippedPoint = insidePoint + distance * ratio;
		}
		if (clippedPoint[i] > getSize(i)) {
			vec3 distance = clippedPoint - insidePoint;
			double newDistanceI = getSize(i) - insidePoint[i];
			double ratio = newDistanceI / distance[i];
			clippedPoint = insidePoint + distance * ratio;
		}
	}

#ifdef _DEBUG
	// Make sure the point is now in the grid:
	if (clippedPoint[0] < 0 || clippedPoint[1] < 0 || clippedPoint[2] < 0 || clippedPoint[0] > getSize(0) || clippedPoint[1] > getSize(1) || clippedPoint[2] > getSize(2)) {
		PRINT_LINE("WARNING: Clipped point is outside grid!");
	}
#endif
	return clippedPoint;

}


double MACGrid::getSize(int dimension) {
	return theDim[dimension] * theCellSize;
}


int MACGrid::getCellIndex(int i, int j, int k)
{
	return i + j * theDim[MACGrid::X] + k * theDim[MACGrid::Y] * theDim[MACGrid::X];
}


int MACGrid::getNumberOfCells()
{
	return theDim[MACGrid::X] * theDim[MACGrid::Y] * theDim[MACGrid::Z];
}

bool MACGrid::isValidCell(int i, int j, int k)
{
	if (i >= theDim[MACGrid::X] || j >= theDim[MACGrid::Y] || k >= theDim[MACGrid::Z]) {
		return false;
	}

	if (i < 0 || j < 0 || k < 0) {
		return false;
	}

	return true;
}

bool MACGrid::isValidFace(int dimension, int i, int j, int k)
{
	if (dimension == 0) {
		if (i > theDim[MACGrid::X] || j >= theDim[MACGrid::Y] || k >= theDim[MACGrid::Z]) {
			return false;
		}
	} else if (dimension == 1) {
		if (i >= theDim[MACGrid::X] || j > theDim[MACGrid::Y] || k >= theDim[MACGrid::Z]) {
			return false;
		}
	} else if (dimension == 2) {
		if (i >= theDim[MACGrid::X] || j >= theDim[MACGrid::Y] || k > theDim[MACGrid::Z]) {
			return false;
		}
	}

	if (i < 0 || j < 0 || k < 0) {
		return false;
	}

	return true;
}

vec3 MACGrid::getFacePosition(int dimension, int i, int j, int k)
{
	if (dimension == 0) {
		return vec3(i * theCellSize, (j + 0.5) * theCellSize, (k + 0.5) * theCellSize);
	} else if (dimension == 1) {
		return vec3((i + 0.5) * theCellSize, j * theCellSize, (k + 0.5) * theCellSize);
	} else if (dimension == 2) {
		return vec3((i + 0.5) * theCellSize, (j + 0.5) * theCellSize, k * theCellSize);
	}

	return vec3(0,0,0); //???

}

double MACGrid::dotProduct(const GridData & vector1, const GridData & vector2) {
	
	double result = 0.0;

	FOR_EACH_CELL {
		result += vector1(i,j,k) * vector2(i,j,k);
	}

	return result;
}

void MACGrid::add(const GridData & vector1, const GridData & vector2, GridData & result) {
	
	FOR_EACH_CELL {
		result(i,j,k) = vector1(i,j,k) + vector2(i,j,k);
	}

}

void MACGrid::subtract(const GridData & vector1, const GridData & vector2, GridData & result) {
	
	FOR_EACH_CELL {
		result(i,j,k) = vector1(i,j,k) - vector2(i,j,k);
	}

}

void MACGrid::multiply(const double scalar, const GridData & vector, GridData & result) {
	
	FOR_EACH_CELL {
		result(i,j,k) = scalar * vector(i,j,k);
	}

}

double MACGrid::maxMagnitude(const GridData & vector) {
	
	double result = 0.0;

	FOR_EACH_CELL {
		if (abs(vector(i,j,k)) > result) result = abs(vector(i,j,k));
	}

	return result;
}


void MACGrid::saveSmoke(const char* fileName) {
	std::ofstream fileOut(fileName);
	if (fileOut.is_open()) {
		FOR_EACH_CELL {
			fileOut << mD(i,j,k) << std::endl;
		}
		fileOut.close();
	}
}

void MACGrid::saveParticle(std::string filename, bool fluidsim)
{
	Partio::ParticlesDataMutable *parts = Partio::create();
	Partio::ParticleAttribute posH, vH;
	posH = parts->addAttribute("position", Partio::VECTOR, 3);
	vH = parts->addAttribute("v", Partio::VECTOR, 3);

    if(fluidsim) {
        for (unsigned int i = 0; i < particles.size(); i++)
        {
            int idx = parts->addParticle();
            float *p = parts->dataWrite<float>(posH, idx);
            float *v = parts->dataWrite<float>(vH, idx);
            for (int k = 0; k < 3; k++)
            {
                p[k] = particles.at(i).position[k];
                v[k] = particles.at(i).velocity[k];
            }
        }
    }
    else {
        for (unsigned int i = 0; i < rendering_particles.size(); i++)
        {
            int idx = parts->addParticle();
            float *p = parts->dataWrite<float>(posH, idx);
            float *v = parts->dataWrite<float>(vH, idx);
            for (int k = 0; k < 3; k++)
            {
                p[k] = rendering_particles[i][k];
                v[k] = rendering_particles_vel[i][k];
            }
        }
    }
	
	Partio::write(filename.c_str(), *parts);
	parts->release();
}

void MACGrid::saveDensity(std::string filename){
	Partio::ParticlesDataMutable *density_field = Partio::create();
	Partio::ParticleAttribute posH, rhoH;
	posH = density_field->addAttribute("position", Partio::VECTOR, 3);
	rhoH = density_field->addAttribute("density", Partio::VECTOR, 1);
	FOR_EACH_CELL{
		int idx = density_field->addParticle();
		float *p = density_field->dataWrite<float>(posH, idx);
		float *rho = density_field->dataWrite<float>(rhoH, idx);
		vec3 cellCenter = getCenter(i, j, k);
		for (int l = 0; l < 3; l++)
		{
			p[l] = cellCenter[l];
		}
		rho[0] = getDensity(cellCenter);
	}
	Partio::write(filename.c_str(), *density_field);
	density_field->release();
}

void MACGrid::draw(const Camera& c)
{
	// drawWireGrid();
	drawSmoke(c);
   drawVelocities();
}

void MACGrid::drawVelocities()
{
   // draw line at each center
   //glColor4f(0.0, 1.0, 0.0, 1.0);
   glBegin(GL_LINES);
      FOR_EACH_CELL_NO_K
      {
         vec3 pos = getCenter(i,j,0);
         vec3 vel = getVelocity(pos);
         if (vel.Length() > 0.0001)
         {
            //vel.Normalize(); 
            vel *= theCellSize/2.0;
            vel += pos;
   		   glColor4f(1.0, 1.0, 0.0, 1.0);
            glVertex2d(1. - 2. * pos.n[0] / (double) theDim[0], 2. * pos.n[1] / (double) theDim[1]);
		      glColor4f(0.0, 1.0, 0.0, 1.0);
            glVertex2d(1. - 2. * vel.n[0] / (double) theDim[0], 2. * vel.n[1] / (double) theDim[1]);
         }
      }
   glEnd();
}

vec4 MACGrid::getRenderColor(int i, int j, int k)
{
	double value = mD(i, j, k); 
	vec4 coldColor(0.5, 0.5, 1, value);
	vec4 hotColor(1, 0.5, 0.5, value);
   return LERP(coldColor, hotColor, mT(i, j, k));

	/*
	// OLD:
    double value = mD(i, j, k); 
    return vec4(1.0, 0.9, 1.0, value);
	*/
}

vec4 MACGrid::getRenderColor(const vec3& pt)
{
	double value = getDensity(pt);
	vec4 coldColor(0.5, 0.5, 1.0, value);
	vec4 hotColor(1.0, 0.5, 0.5, value);
   return LERP(coldColor, hotColor, getTemperature(pt));

	/*
	// OLD:
    double value = getDensity(pt); 
    return vec4(1.0, 1.0, 1.0, value);
	*/
}

void MACGrid::drawSmoke(const Camera& c)
{
    //used in this project
   // Draw K Sheets from back to front
   double back =  (theDim[2])*theCellSize;
   double top  =  (theDim[1])*theCellSize;
   double right = (theDim[0])*theCellSize;
  
   double stepsize = theCellSize * 0.25;

   double startk = back - stepsize;
   double endk = 0;
   double stepk = -theCellSize;

   for (double j = 0.0; j < top; j += stepsize)
   {
      glBegin(GL_QUAD_STRIP);
      for (double i = right; i >= 0; i -= stepsize)
      {
         vec3 pos1 = vec3(i,j,startk); 
         vec3 pos2 = vec3(i, j+stepsize, startk); 
         vec4 color1, color2;
         if (allowsphere == 1) {
         // --------sphere--------
            int centerX = sphereC[0]*theCellSize, centerY = sphereC[1]*theCellSize, radius = rr2;
            double distSphere = std::sqrt((i-centerX)*(i-centerX)+(j-centerY)*(j-centerY));
            if (distSphere<=radius) {
               //reflect color
               color1 = vec4 (1,1,1, 1-distSphere/radius/2);
               color2 = vec4 (1,1,1, 1-distSphere/radius/2);
               //absorb color
               //color1 = vec4 (1,0,1, 1-distSphere/radius/2);
               //color2 = vec4 (1,0,1, 1-distSphere/radius/2);
               //attract color
               //color1 = vec4 (0.9,0.6,0.2, 1-distSphere/radius/2);
               //color2 = vec4 (0.9,0.6,0.2, 1-distSphere/radius/2);
            } else {
               color1 = getRenderColor(pos1);
               color2 = getRenderColor(pos2);
            }
               //---------------------
         } else {
            color1 = getRenderColor(pos1);
            color2 = getRenderColor(pos2);
         }
         glColor4dv(color1.n);
         glVertex2d((right - i) / right, j / top);
         glColor4dv(color2.n);
         glVertex2d((right - i) / right, (j + stepsize) / top);
      } 
      glEnd();
   }
}


void MACGrid::drawWireGrid()
{
   // Display grid in light grey, draw top & bottom

   double xstart = 0.0;
   double ystart = 0.0;
   double zstart = 0.0;
   double xend = theDim[0]*theCellSize;
   double yend = theDim[1]*theCellSize;
   double zend = theDim[2]*theCellSize;

   glPushAttrib(GL_LIGHTING_BIT | GL_LINE_BIT);
      glDisable(GL_LIGHTING);
      glColor3f(0.25, 0.25, 0.25);

      glBegin(GL_LINES);
      for (int i = 0; i <= theDim[0]; i++)
      {
         double x = xstart + i*theCellSize;
         glVertex3d(x, ystart, zstart);
         glVertex3d(x, ystart, zend);

         glVertex3d(x, yend, zstart);
         glVertex3d(x, yend, zend);
      }

      for (int i = 0; i <= theDim[2]; i++)
      {
         double z = zstart + i*theCellSize;
         glVertex3d(xstart, ystart, z);
         glVertex3d(xend, ystart, z);

         glVertex3d(xstart, yend, z);
         glVertex3d(xend, yend, z);
      }

      glVertex3d(xstart, ystart, zstart);
      glVertex3d(xstart, yend, zstart);

      glVertex3d(xend, ystart, zstart);
      glVertex3d(xend, yend, zstart);

      glVertex3d(xstart, ystart, zend);
      glVertex3d(xstart, yend, zend);

      glVertex3d(xend, ystart, zend);
      glVertex3d(xend, yend, zend);
      glEnd();
   glPopAttrib();

   glEnd();
}