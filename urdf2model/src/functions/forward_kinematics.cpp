#include "forward_kinematics.hpp"

// TODO: Allow the user to request a fk function with all desired outputs (where the user must input an array of strings containing the frame names)

namespace mecali
{
  casadi::Function get_forward_kinematics_position(CasadiModel &cas_model, CasadiData &cas_data, std::string frame_name)
  {
    int                 EE_idx = cas_model.getFrameId(frame_name);
    std::cout << "The frame with name: " << frame_name << " has an index of: " << EE_idx << std::endl;
    // Set variables
    CasadiScalar        q_sx = casadi::SX::sym("q", cas_model.nq);
    ConfigVectorCasadi  q_casadi(cas_model.nq);
    pinocchio::casadi::copy( q_sx, q_casadi );

    // Call the forward kinematics function
    pinocchio::forwardKinematics(     cas_model,   cas_data,    q_casadi);
    pinocchio::updateFramePlacements( cas_model,   cas_data);

    // Get the result from FK
    CasadiScalar        pos_sx(3,1);
    pinocchio::casadi::copy( cas_data.oMf[EE_idx].translation(), pos_sx );

    // Create the Forward Kinematics function
    casadi::Function    fk_pos( "fk_pos", casadi::SXVector {q_sx}, casadi::SXVector {pos_sx} );

    return fk_pos;
  }
  casadi::Function get_forward_kinematics_position(CasadiModel &cas_model, CasadiData &cas_data)
  {
    int                 EE_idx = cas_model.nframes-1;
    // Set variables
    CasadiScalar        q_sx = casadi::SX::sym("q", cas_model.nq);
    ConfigVectorCasadi  q_casadi(cas_model.nq);
    pinocchio::casadi::copy( q_sx, q_casadi );

    // Call the forward kinematics function
    pinocchio::forwardKinematics(     cas_model,   cas_data,    q_casadi);
    pinocchio::updateFramePlacements( cas_model,   cas_data);

    // Get the result from FK
    CasadiScalar        pos_sx(3,1);
    pinocchio::casadi::copy( cas_data.oMf[EE_idx].translation(), pos_sx );

    // Create the Forward Kinematics function
    casadi::Function    fk_pos( "fk_pos", casadi::SXVector {q_sx}, casadi::SXVector {pos_sx} );

    return fk_pos;
  }
  casadi::Function get_forward_kinematics_rotation(CasadiModel &cas_model, CasadiData &cas_data, std::string frame_name)
  {
    int                 EE_idx = cas_model.getFrameId(frame_name);
    std::cout << "The frame with name: " << frame_name << " has an index of: " << EE_idx << std::endl;
    // Set variables
    CasadiScalar        q_sx = casadi::SX::sym("q", cas_model.nq);
    ConfigVectorCasadi  q_casadi(cas_model.nq);
    pinocchio::casadi::copy( q_sx, q_casadi );

    // Call the forward kinematics function
    pinocchio::forwardKinematics(     cas_model,   cas_data,    q_casadi);
    pinocchio::updateFramePlacements( cas_model,   cas_data);

    // Get the result from FK
    CasadiScalar        rot_sx(3,3);
    for(Eigen::DenseIndex i = 0; i < 3; ++i)
    {
      for(Eigen::DenseIndex j = 0; j < 3; ++j)
      {
        rot_sx(i,j) = cas_data.oMf[EE_idx].rotation()(i,j);
      }
    }

    // Create the Forward Kinematics function
    casadi::Function    fk_rot( "fk_rot", casadi::SXVector {q_sx}, casadi::SXVector {rot_sx} );

    return fk_rot;
  }
  casadi::Function get_forward_kinematics_rotation(CasadiModel &cas_model, CasadiData &cas_data)
  {
    int                 EE_idx = cas_model.nframes-1;
    // Set variables
    CasadiScalar        q_sx = casadi::SX::sym("q", cas_model.nq);
    ConfigVectorCasadi  q_casadi(cas_model.nq);
    pinocchio::casadi::copy( q_sx, q_casadi );

    // Call the forward kinematics function
    pinocchio::forwardKinematics(     cas_model,   cas_data,    q_casadi);
    pinocchio::updateFramePlacements( cas_model,   cas_data);

    // Get the result from FK
    CasadiScalar        rot_sx(3,3);
    for(Eigen::DenseIndex i = 0; i < 3; ++i)
    {
      for(Eigen::DenseIndex j = 0; j < 3; ++j)
      {
        rot_sx(i,j) = cas_data.oMf[EE_idx].rotation()(i,j);
      }
    }

    // Create the Forward Kinematics function
    casadi::Function    fk_rot( "fk_rot", casadi::SXVector {q_sx}, casadi::SXVector {rot_sx} );

    return fk_rot;
  }
}
