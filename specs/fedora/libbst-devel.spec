#
# spec file for library libbst-devel
#
# Copyright (c) 2024 Michael Berry <trismegustis@gmail.com>
#


Name:           libbst-devel
Version:        0.1.1
Release:        1
License:        MIT
Summary:        Generically typed C library for creating self balanced binary trees
Url:            https://github.com/berrym/bst
Source:         https://github.com/berrym/release/libbst-%{version}.tar.gz
BuildRequires:  gcc
BuildRequires:  meson
Requires:       glibc

%description
A generically typed C library for creating self balancing AVL Binary Trees.

%prep
%setup -q -n libbst

%build
%meson
%meson_build

%install
%meson_install

%check
%meson_test

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%doc README.md
%{_libdir}/libbst.so
%{_includedir}/bst.h
%{_includedir}/errors.h

%changelog
* Sun Aug 11 2024 Michael Berry <trismegustis@gmail.com> - 0.1.1-1
- rebuilt
