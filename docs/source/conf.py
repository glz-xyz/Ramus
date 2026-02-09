import os
import sys

project = 'Ramus'
copyright = '2026, Simon Gleizes'
author = 'Simon Gleizes (@glz-xyz)'

extensions = [
    'breathe',
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon'
]

breathe_projects = { "Ramus": "../../build/xml" }
breathe_default_project = "Ramus"

html_theme = 'sphinx_rtd_theme'