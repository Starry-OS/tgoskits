# Asking Star Soil Component

This is the local TGOSKits scheme-B import of the Asking Star soil boundary.

For the full Asking Star Scheme-B functional layout and evidence boundary, see docs/docs/asking-star/scheme-b-overview.md.

Scope:

- `SoilRuntime` and kernel request/result conversion
- mock/Linux-user/StarryOS adapter surfaces
- StarryOS dry-run and QEMU observation bridges
- guards that prevent dry-run or host mock evidence from being reported as BoardReal evidence

This component is a host-side smoke layer. It does not replace real StarryOS board evidence or TGOSKits root CI.
