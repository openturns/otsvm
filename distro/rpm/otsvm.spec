# norootforbuild
%global python_sitearch %{_libdir}/python%(python3 -c "import sysconfig; print(sysconfig.get_python_version())")/site-packages

Name:           otsvm
Version:        0.17
Release:        0%{?dist}
Summary:        OpenTURNS module
Group:          System Environment/Libraries
License:        LGPLv3+
URL:            http://www.openturns.org/
Source0:        http://downloads.sourceforge.net/openturns-modules/otsvm/otsvm-%{version}.tar.bz2
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires:  gcc-c++, cmake, swig
BuildRequires:  openturns-devel
BuildRequires:  python3-openturns
BuildRequires:  python3-devel
Requires:       libotsvm0

%description
SVM module for OpenTURNS library.

%package -n libotsvm0
Summary:        OTSVM development files
Group:          Development/Libraries/C and C++

%description -n libotsvm0
Development libraries for OTSVM library.

%package devel
Summary:        OTSVM development files
Group:          Development/Libraries/C and C++
Requires:       libotsvm0 = %{version}
Requires:       openturns-devel

%description devel
Development files for OTSVM library.

%package -n python3-%{name}
Summary:        OTSVM library
Group:          Productivity/Scientific/Math
Requires:       python3-openturns
%description -n python3-%{name}
Python textual interface to OTSVM uncertainty library

%prep
%setup -q

%build
%cmake -DINSTALL_DESTDIR:PATH=%{buildroot} \
       -DCMAKE_SKIP_INSTALL_RPATH:BOOL=ON \
       -DCMAKE_UNITY_BUILD=ON .
%cmake_build

%install
%cmake_install

%check
export LD_LIBRARY_PATH=%{buildroot}%{_libdir}
%ctest --tests-regex pyinstallcheck --schedule-random

%post -n libotsvm0 -p /sbin/ldconfig 
%postun -n libotsvm0 -p /sbin/ldconfig 

%files -n libotsvm0
%defattr(-,root,root,-)
%{_libdir}/*.so.*

%files devel
%defattr(-,root,root,-)
%dir %{_includedir}/%{name}
%{_includedir}/%{name}/*.h*
%{_includedir}/%{name}/swig/
%{_libdir}/*.so
%{_libdir}/cmake/

%files -n python3-%{name}
%defattr(-,root,root,-)
%{python_sitearch}/%{name}/
%{python_sitearch}/%{name}-*.dist-info/


%changelog
* Wed Nov 28 2012 Julien Schueller <schueller at phimeca dot com> 0.0-1
- Initial package creation

