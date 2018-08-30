#include "gaussian2D_rot.h"

using namespace nest;

namespace nest
{

RotGaussian2DParameter::RotGaussian2DParameter( const DictionaryDatum& d )
  : p_center_( 1.0 )
  , mean_x_( 0.0 )
  , sigma_x_( 1.0 )
  , mean_y_( 0.0 )
  , sigma_y_( 1.0 )
  , theta_( 0.0 )
{
  updateValue< double >( d, names::p_center, p_center_ );
  updateValue< double >( d, names::mean_x, mean_x_ );
  updateValue< double >( d, names::sigma_x, sigma_x_ );
  updateValue< double >( d, names::mean_y, mean_y_ );
  updateValue< double >( d, names::sigma_y, sigma_y_ );
  updateValue< double >( d, names::theta, theta_ );
  if ( sigma_x_ <= 0 || sigma_y_ <= 0 )
  {
    throw BadProperty(
      "topology::Gaussian2DParameter: "
      "sigma_x > 0 and sigma_y > 0 required." );
  }
}


}  // namespace nest