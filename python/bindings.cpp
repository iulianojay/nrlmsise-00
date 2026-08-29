#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <nrlmsise00/Nrlmsise00.hpp>

namespace py = pybind11;

PYBIND11_MODULE(nrlmsise00, m)
{
    m.doc() = "Python bindings for the NRLMSISE-00 atmosphere model";

    py::class_<atmos::Nrlmsise00>(m, "Nrlmsise00")
        .def(py::init([](const std::array<int, 24>& flags) { return new atmos::Nrlmsise00(flags); }), py::arg("flags"), "Construct with explicit flags array (24 elements, 0=off, 1=on, 2=cross terms only)")
        .def(
            py::init([]() {
                std::array<int, 24> flags;
                flags.fill(1);
                return new atmos::Nrlmsise00(flags);
            }),
            "Construct with all flags set to 1 (default)"
        )
        .def(
            "density",
            [](atmos::Nrlmsise00& self,
               const int doy,
               const double sec,
               const double alt,
               const double g_lat,
               const double g_long,
               const double f107A,
               const double f107,
               std::array<double, 7> ap) { return self.density(doy, sec, alt, g_lat, g_long, f107A, f107, ap); },
            py::arg("doy"),
            py::arg("sec"),
            py::arg("alt"),
            py::arg("g_lat"),
            py::arg("g_long"),
            py::arg("f107A"),
            py::arg("f107"),
            py::arg("ap"),
            "Compute the effective total mass density including anomalous oxygen contribution.\n"
            "Returns density in g/cm^3 (or kg/m^3 if flag 0 is set)."
        );
}
