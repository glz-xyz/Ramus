import os
import sys

project = 'Ramus'
copyright = '2026, Simon Gleizes'
author = 'Simon Gleizes (@glz-xyz)'

extensions = [
    'breathe',
    'exhale',
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon'
]

breathe_projects = { "Ramus": "../../build/xml" }
breathe_default_project = "Ramus"

exhale_args = {
    "containmentFolder":     "./api",
    "rootFileName":          "library_root.rst",
    "rootFileTitle":         "Library API",
    "doxygenStripFromPath":  "..",
    "headingLevel":          3,
    "createTreeView":        True,
    "exhaleExecutesDoxygen": False,
}

primary_domain = 'cpp'
highlight_language = 'cpp'

html_theme = 'sphinx_rtd_theme'