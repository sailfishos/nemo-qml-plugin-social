Name:       nemo-qml-plugin-social-qt5

Summary:    Social plugin for Nemo Mobile
Version:    0.0.0
Release:    1
Group:      System/Libraries
License:    BSD
URL:        https://git.merproject.org/mer-core/nemo-qml-plugin-social
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Test)

%description
%{summary}.

%package tests
Summary:    Social QML adapters for Nemo - unit tests
Group:      System/Libraries
Requires:   %{name} = %{version}-%{release}

%description tests
This package includes the unit tests.


%prep
%setup -q -n %{name}-%{version}

%build
%qmake5 

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%qmake5_install

%files
%defattr(-,root,root,-)
%{_libdir}/qt5/qml/org/nemomobile/social/libnemosocial.so
%{_libdir}/qt5/qml/org/nemomobile/social/qmldir

%files tests
%defattr(-,root,root,-)
/opt/tests/nemo-qml-plugins-qt5/social/facebooksocialtest
/opt/tests/nemo-qml-plugins-qt5/social/twittersocialtest
/opt/tests/nemo-qml-plugins-qt5/social/share/*.qml
