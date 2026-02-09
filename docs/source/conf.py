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

exhale_args = {
    "containmentFolder":     "./api",
    "rootFileName":          "library_root.rst",
    "rootFileTitle":         "Library API",
    "doxygenStripFromPath":  "..",
    "headingLevel":          3,
    "createTreeView":        True,
    "exhaleExecutesDoxygen": False,
}

breathe_projects = { "Ramus": "../../build/xml" }
breathe_default_project = "Ramus"

primary_domain = 'cpp'
highlight_language = 'cpp'

html_theme = 'sphinx_rtd_theme'