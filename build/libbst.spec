Name: libbst
Version: v0.1.0
Release: 1%{?dist}
Summary: Simple binary search tree library
License: MIT

URL: https://github.com/berrym/bst
Source0: %{URL}/archive/%{version}.tar.gz

BuildRequires: meson
BuildRequires: gcc

%description
A small simple binary search tree library written in c.

%package devel
Summary: Development files for %{name}


%description devel
Development files for %{name}.

%prep
%autosetup

%build
%meson
%meson_build

%install
%meson_install

%check
%meson_test

%files
%{_libdir}/libbst.so

%files devel
%{_includedir}/bst.h
%{_includedir}/errors.h

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%changelog
* Mon Aug 17 2020 Michael Berry <trismegustis@gmail.com> - 
- 

