#include <casadi/casadi.hpp>
#include "model_pinocchio/pinocchio_interface.h"

using namespace casadi;

int main(int argc, char ** argv)
{
    // Select the URDF file to create the model
    std::string filename = (argc<=1) ? "../urdf2model/robot_descriptions/kortex_description/urdf/JACO3_URDF_V11.urdf" : argv[1];
        // ../urdf2model/robot_descriptions/kortex_description/urdf/JACO3_URDF_V10rev.urdf
        // ../urdf2model/robot_descriptions/kortex_description/urdf/JACO3_URDF_V11.urdf
        // ../urdf2model/robot_descriptions/iiwa_description/urdf/iiwa14.urdf
        // ../urdf2model/robot_descriptions/abb_common/urdf/irb120.urdf

    robot_init(filename);
    // execute_tests();

    test_casadi_aba();
    test_casadi_rnea();
    test_casadi_fk();

    #ifdef DEBUG
      print_model_data();
    #endif

    int n_dof = get_ndof();

    // std::cout << "ndof: " << n_dof << std::endl;

    // Variables
    SX q = SX::sym("q",n_dof,1);
    SX qd = SX::sym("qd",n_dof,1);
    SX qdd = SX::zeros(n_dof,1);
    SX tau = SX::sym("tau",n_dof,1);


    // CasadiModel cas_model;
    // CasadiData cas_data(cas_model);
    // generate_model(cas_model, cas_data, "../urdf2model/robot_descriptions/abb_common/urdf/irb120.urdf");
    //
    // std::cout << "name: " << cas_model.name << std::endl;
}
