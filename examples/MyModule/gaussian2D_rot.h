#include "topologymodule.h"
#include "topology_parameter.h"

using namespace nest;

namespace mynest
{

/*
Rotated 2D gaussian

# def RotGaussian2D(x, y,
#                p_center=1.,
#                sigma_x=1.,
#                sigma_y=1.,
#                mean_x=0.,
#                mean_y=0.,
#                theta=0.
#               ):
#     '''
#     Parameters
#     ----------
#     x : float, x-position
#     y : float, y-positon
#     p_center : float, center probability
#     sigma_x : float, st.dev along x-axis
#     sigma_y : float, st.dev along y-axis
#     mean_x : float, mean along x-axis
#     mean_y : float, mean along y-axis
#     theta : float, rotation (rad) 
#     
#     Returns
#     -------
#     float : 
#     '''
#     
#     a = np.cos(theta)**2/(2*sigma_x**2) + np.sin(theta)**2/(2*sigma_y**2)
#     b = -np.sin(2*theta)/(4*sigma_x**2) + np.sin(2*theta)/(4*sigma_y**2)
#     c = np.sin(theta)**2/(2*sigma_x**2) + np.cos(theta)**2/(2*sigma_y**2)
# 
#     return p_center*np.exp( - (a*(x-mean_x)**2 + 2*b*(x-mean_x)*(y-mean_y) + c*(y-mean_y)**2))

 */

class RotGaussian2DParameter : public TopologyParameter
{
public:
  /**
   * Parameters:
   * p_center - value at center
   * mean_x   - x-coordinate of center
   * mean_y   - y-coordinate of center
   * sigma_x  - width in x-direction
   * sigma_y  - width in y-direction
   * theta    - rotation (rad)
   */
  RotGaussian2DParameter( const DictionaryDatum& d );

  double
  raw_value( const Position< 2 >& pos, librandom::RngPtr& ) const
  {
    return p_center_ * std::exp( - ( a_( theta_, sigma_x_, sigma_y_) * std::pow( ( pos[ 0 ] - mean_x_ ) , 2 ) +
                                    2 * b_( theta_, sigma_x_, sigma_y_ ) * ( pos[ 0 ] - mean_x_ ) * ( pos[ 1 ] - mean_y_ ) +
                                    c_( theta_, sigma_x_, sigma_y_ ) * std::pow( ( pos[ 1 ] - mean_y_ ) , 2 ) ) );
  }

  double
  raw_value( const Position< 3 >& pos, librandom::RngPtr& rng ) const
  {
    return raw_value( Position< 2 >( pos[ 0 ], pos[ 1 ] ), rng );
  }

  double
  a_( const double theta_, const double sigma_x_, const double sigma_y_) const
  {
    return std::pow( std::cos( theta_ ), 2 ) / ( 2 * std::pow( sigma_x_ , 2 ) ) +
        std::pow( std::sin( theta_ ), 2) / ( 2 * std::pow( sigma_y_, 2 ) );
  }

  double
  b_( const double theta_, const double sigma_x_, const double sigma_y_) const
  {
    return -std::sin( 2 * theta_ ) / ( 4 * std::pow( sigma_x_ , 2 ) ) +
        std::sin( 2 * theta_ ) / ( 4 * std::pow( sigma_y_ , 2 ) );
  }

  double
  c_( const double theta_, const double sigma_x_, const double sigma_y_) const
  {
    return std::pow( std::sin( theta_ ) , 2 ) / ( 2 * std::pow( sigma_x_ , 2 ) ) +
      std::pow( std::cos( theta_ ), 2 ) / ( 2 * std::pow( sigma_y_ , 2 ) );    
  }

  TopologyParameter*
  clone() const
  {
    return new RotGaussian2DParameter( *this );
  }

private:
  double p_center_, mean_x_, sigma_x_, mean_y_, sigma_y_, theta_;
};

} // namespace mynest